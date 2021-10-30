#pragma once

extern "C" {
#include "sai.h"
}

#include <string>
#include <unordered_map>

// TODO: Move the rest of AclTable implementation out of AclOrch

#define ACL_TABLE_DESCRIPTION  "POLICY_DESC"
#define ACL_TABLE_STAGE        "STAGE"
#define ACL_TABLE_TYPE         "TYPE"
#define ACL_TABLE_PORTS        "PORTS"
#define ACL_TABLE_SERVICES     "SERVICES"

#define STAGE_INGRESS  "INGRESS"
#define STAGE_EGRESS   "EGRESS"
#define STAGE_PRE_INGRESS "PRE_INGRESS"

#define TABLE_TYPE_L3                   "L3"
#define TABLE_TYPE_L3V6                 "L3V6"
#define TABLE_TYPE_MIRROR               "MIRROR"
#define TABLE_TYPE_MIRRORV6             "MIRRORV6"
#define TABLE_TYPE_MIRROR_DSCP          "MIRROR_DSCP"
#define TABLE_TYPE_PFCWD                "PFCWD"
#define TABLE_TYPE_CTRLPLANE            "CTRLPLANE"
#define TABLE_TYPE_DTEL_FLOW_WATCHLIST  "DTEL_FLOW_WATCHLIST"
#define TABLE_TYPE_DTEL_DROP_WATCHLIST  "DTEL_DROP_WATCHLIST"
#define TABLE_TYPE_MCLAG                "MCLAG"
#define TABLE_TYPE_MUX                  "MUX"
#define TABLE_TYPE_DROP                 "DROP"

typedef enum
{
    ACL_STAGE_UNKNOWN,
    ACL_STAGE_INGRESS,
    ACL_STAGE_EGRESS,
    ACL_STAGE_PRE_INGRESS
} acl_stage_type_t;

typedef std::unordered_map<std::string, acl_stage_type_t> acl_stage_type_lookup_t;

typedef enum
{
    ACL_TABLE_UNKNOWN,
    ACL_TABLE_L3,
    ACL_TABLE_L3V6,
    ACL_TABLE_MIRROR,
    ACL_TABLE_MIRRORV6,
    ACL_TABLE_MIRROR_DSCP,
    ACL_TABLE_PFCWD,
    ACL_TABLE_CTRLPLANE,
    ACL_TABLE_DTEL_FLOW_WATCHLIST,
    ACL_TABLE_DTEL_DROP_WATCHLIST,
    ACL_TABLE_MCLAG,
    ACL_TABLE_MUX,
    ACL_TABLE_DROP,
    ACL_TABLE_PBH
} acl_table_type_t;

typedef std::unordered_map<std::string, acl_table_type_t> acl_table_type_lookup_t;
typedef std::map<std::string, sai_acl_stage_t> acl_stage_lookup_t;
typedef std::map<sai_acl_stage_t, sai_switch_attr_t> acl_stage_to_switch_attr_lookup_t;

struct AclTableGroupMember {
    sai_object_id_t m_group_oid;
    sai_object_id_t m_group_member_oid;
    uint32_t m_priority;
    AclTableGroupMember()
        : m_group_oid(SAI_NULL_OBJECT_ID)
        , m_group_member_oid(SAI_NULL_OBJECT_ID)
        , m_priority(0)
    {}
};

static const acl_stage_lookup_t aclStageLookup = {
    {STAGE_INGRESS, SAI_ACL_STAGE_INGRESS},
    {STAGE_EGRESS, SAI_ACL_STAGE_EGRESS},
    {STAGE_PRE_INGRESS, SAI_ACL_STAGE_PRE_INGRESS},
};

static const acl_stage_to_switch_attr_lookup_t aclStageToSwitchAttrLookup = {
    {SAI_ACL_STAGE_INGRESS, SAI_SWITCH_ATTR_INGRESS_ACL},
    {SAI_ACL_STAGE_EGRESS, SAI_SWITCH_ATTR_EGRESS_ACL},
    {SAI_ACL_STAGE_PRE_INGRESS, SAI_SWITCH_ATTR_PRE_INGRESS_ACL},
};