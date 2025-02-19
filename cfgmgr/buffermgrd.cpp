#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <mutex>
#include "dbconnector.h"
#include "select.h"
#include "exec.h"
#include "schema.h"
#include "buffermgr.h"
#include "buffermgrdyn.h"
#include <fstream>
#include <iostream>
#include "json.h"
#include "json.hpp"

using namespace std;
using namespace swss;
using json = nlohmann::json;

/* SELECT() function timeout retry time, in millisecond */
#define SELECT_TIMEOUT 1000

/*
 * Following global variables are defined here for the purpose of
 * using existing Orch class which is to be refactored soon to
 * eliminate the direct exposure of the global variables.
 *
 * Once Orch class refactoring is done, these global variables
 * should be removed from here.
 */
int gBatchSize = 0;
bool gSwssRecord = false;
bool gLogRotate = false;
ofstream gRecordOfs;
string gRecordFile;
bool gResponsePublisherRecord = false;
bool gResponsePublisherLogRotate = false;
ofstream gResponsePublisherRecordOfs;
string gResponsePublisherRecordFile;
/* Global database mutex */
mutex gDbMutex;

void usage()
{
    cout << "Usage: buffermgrd <-l pg_lookup.ini|-a asic_table.json [-p peripheral_table.json]>" << endl;
    cout << "       -l pg_lookup.ini: PG profile look up table file (mandatory for static mode)" << endl;
    cout << "           format: csv" << endl;
    cout << "           values: 'speed, cable, size, xon,  xoff, dynamic_threshold, xon_offset'" << endl;
    cout << "       -a asic_table.json: ASIC-specific parameters definition (mandatory for dynamic mode)" << endl;
    cout << "       -p peripheral_table.json: Peripheral (eg. gearbox) parameters definition (mandatory for dynamic mode)" << endl;
}

void dump_db_item(KeyOpFieldsValuesTuple &db_item)
{
    SWSS_LOG_DEBUG("db_item: [");
    SWSS_LOG_DEBUG("\toperation: %s", kfvOp(db_item).c_str());
    SWSS_LOG_DEBUG("\thash: %s", kfvKey(db_item).c_str());
    SWSS_LOG_DEBUG("\tfields: [");
    for (auto fv: kfvFieldsValues(db_item))
        SWSS_LOG_DEBUG("\t\tfield: %s value: %s", fvField(fv).c_str(), fvValue(fv).c_str());
    SWSS_LOG_DEBUG("\t]");
    SWSS_LOG_DEBUG("]");
}

void write_to_state_db(shared_ptr<vector<KeyOpFieldsValuesTuple>> db_items_ptr)
{
    DBConnector db("STATE_DB", 0, true);
    auto &db_items = *db_items_ptr;
    for (auto &db_item : db_items)
    {
        dump_db_item(db_item);

        string key = kfvKey(db_item);
        size_t pos = key.find(":");
        if ((string::npos == pos) || ((key.size() - 1) == pos))
        {
            SWSS_LOG_ERROR("Invalid formatted hash:%s\n", key.c_str());
            return;
        }
        string table_name = key.substr(0, pos);
        string key_name = key.substr(pos + 1);
        Table stateTable(&db, table_name);

        stateTable.set(key_name, kfvFieldsValues(db_item), SET_COMMAND);
    }
}

shared_ptr<vector<KeyOpFieldsValuesTuple>> load_json(string file)
{
    try
    {
        ifstream json(file);
        auto db_items_ptr = make_shared<vector<KeyOpFieldsValuesTuple>>();

        if (!JSon::loadJsonFromFile(json, *db_items_ptr))
        {
            db_items_ptr.reset();
            return nullptr;
        }

        return db_items_ptr;
    }
    catch (...)
    {
        SWSS_LOG_WARN("Loading file %s failed", file.c_str());
        return nullptr;
    }
}

int main(int argc, char **argv)
{
    int opt;
    string pg_lookup_file = "";
    string asic_table_file = "";
    string peripherial_table_file = "";
    string json_file = "";
    Logger::linkToDbNative("buffermgrd");
    SWSS_LOG_ENTER();

    SWSS_LOG_NOTICE("--- Starting buffermgrd ---");

    while ((opt = getopt(argc, argv, "l:a:p:h")) != -1 )
    {
        switch (opt)
        {
        case 'l':
            pg_lookup_file = optarg;
            break;
        case 'h':
            usage();
            return 1;
        case 'a':
            asic_table_file = optarg;
            break;
        case 'p':
            peripherial_table_file = optarg;
            break;
        default: /* '?' */
            usage();
            return EXIT_FAILURE;
        }
    }

    try
    {
        std::vector<Orch *> cfgOrchList;
        bool dynamicMode = false;
        shared_ptr<vector<KeyOpFieldsValuesTuple>> db_items_ptr;

        DBConnector cfgDb("CONFIG_DB", 0);
        DBConnector stateDb("STATE_DB", 0);
        DBConnector applDb("APPL_DB", 0);

        if (!asic_table_file.empty())
        {
            // Load the json file containing the SWITCH_TABLE
            db_items_ptr = load_json(asic_table_file);
            if (nullptr != db_items_ptr)
            {
                write_to_state_db(db_items_ptr);
                db_items_ptr.reset();

                if (!peripherial_table_file.empty())
                {
                    //Load the json file containing the PERIPHERIAL_TABLE
                    db_items_ptr = load_json(peripherial_table_file);
                    if (nullptr != db_items_ptr)
                        write_to_state_db(db_items_ptr);
                }

                dynamicMode = true;
            }
        }

        if (dynamicMode)
        {
            vector<TableConnector> buffer_table_connectors = {
                TableConnector(&cfgDb, CFG_PORT_TABLE_NAME),
                TableConnector(&cfgDb, CFG_PORT_CABLE_LEN_TABLE_NAME),
                TableConnector(&cfgDb, CFG_BUFFER_POOL_TABLE_NAME),
                TableConnector(&cfgDb, CFG_BUFFER_PROFILE_TABLE_NAME),
                TableConnector(&cfgDb, CFG_BUFFER_PG_TABLE_NAME),
                TableConnector(&cfgDb, CFG_BUFFER_QUEUE_TABLE_NAME),
                TableConnector(&cfgDb, CFG_BUFFER_PORT_INGRESS_PROFILE_LIST_NAME),
                TableConnector(&cfgDb, CFG_BUFFER_PORT_EGRESS_PROFILE_LIST_NAME),
                TableConnector(&cfgDb, CFG_DEFAULT_LOSSLESS_BUFFER_PARAMETER),
                TableConnector(&stateDb, STATE_BUFFER_MAXIMUM_VALUE_TABLE),
                TableConnector(&stateDb, STATE_PORT_TABLE_NAME)
            };
            cfgOrchList.emplace_back(new BufferMgrDynamic(&cfgDb, &stateDb, &applDb, buffer_table_connectors, db_items_ptr));
        }
        else if (!pg_lookup_file.empty())
        {
            vector<string> cfg_buffer_tables = {
                CFG_PORT_TABLE_NAME,
                CFG_PORT_CABLE_LEN_TABLE_NAME,
                CFG_BUFFER_POOL_TABLE_NAME,
                CFG_BUFFER_PROFILE_TABLE_NAME,
                CFG_BUFFER_PG_TABLE_NAME,
                CFG_BUFFER_QUEUE_TABLE_NAME,
                CFG_BUFFER_PORT_INGRESS_PROFILE_LIST_NAME,
                CFG_BUFFER_PORT_EGRESS_PROFILE_LIST_NAME,
                CFG_DEVICE_METADATA_TABLE_NAME
            };
            cfgOrchList.emplace_back(new BufferMgr(&cfgDb, &applDb, pg_lookup_file, cfg_buffer_tables));
        }
        else
        {
            usage();
            return EXIT_FAILURE;
        }

        auto buffmgr = cfgOrchList[0];

        swss::Select s;
        for (Orch *o : cfgOrchList)
        {
            s.addSelectables(o->getSelectables());
        }

        SWSS_LOG_NOTICE("starting main loop");
        while (true)
        {
            Selectable *sel;
            int ret;

            ret = s.select(&sel, SELECT_TIMEOUT);
            if (ret == Select::ERROR)
            {
                SWSS_LOG_NOTICE("Error: %s!", strerror(errno));
                continue;
            }
            if (ret == Select::TIMEOUT)
            {
                buffmgr->doTask();
                continue;
            }

            auto *c = (Executor *)sel;
            c->execute();
        }
    }
    catch(const std::exception &e)
    {
        SWSS_LOG_ERROR("Runtime error: %s", e.what());
    }
    return -1;
}
