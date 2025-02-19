# Lint as: python3
from swsscommon import swsscommon

import time
import util
import json

INGRESS_STAGE = "SAI_ACL_STAGE_INGRESS"
EGRESS_STAGE = "SAI_ACL_STAGE_EGRESS"
PRE_INGRESS_STAGE = "SAI_ACL_STAGE_PRE_INGRESS"

class P4RtAclTableDefinitionWrapper(util.DBInterface):
    """Interface to interact with APP DB and ASIC DB tables for P4RT ACL table definition object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_ACL_TABLE"
    SAI_ATTR_MATCH_ETHER_TYPE = "SAI_ACL_TABLE_ATTR_FIELD_ETHER_TYPE"
    SAI_ATTR_MATCH_IP_TYPE = "SAI_ACL_TABLE_ATTR_FIELD_ACL_IP_TYPE"
    SAI_ATTR_MATCH_DST_MAC = "SAI_ACL_TABLE_ATTR_FIELD_DST_MAC"
    SAI_ATTR_MATCH_SRC_IPV6_WORD3 = "SAI_ACL_TABLE_ATTR_FIELD_SRC_IPV6_WORD3"
    SAI_ATTR_MATCH_SRC_IPV6_WORD2 = "SAI_ACL_TABLE_ATTR_FIELD_SRC_IPV6_WORD2"
    SAI_ATTR_MATCH_UDF_GROUP_MIN = "SAI_ACL_TABLE_ATTR_USER_DEFINED_FIELD_GROUP_MIN"
    SAI_ATTR_MATCH_UDF_GROUP_1 = "SAI_ACL_TABLE_ATTR_USER_DEFINED_FIELD_GROUP_1"
    SAI_ATTR_ACTION_TYPE_LIST = "SAI_ACL_TABLE_ATTR_ACL_ACTION_TYPE_LIST"
    SAI_ACL_TABLE_ATTR_ACL_STAGE = "SAI_ACL_TABLE_ATTR_ACL_STAGE"
    SAI_ACL_TABLE_ATTR_SIZE = "SAI_ACL_TABLE_ATTR_SIZE"

    # table name in APP_DB and attribute fields
    APP_DB_TBL_NAME = swsscommon.APP_P4RT_TABLE_NAME
    TBL_NAME = swsscommon.APP_P4RT_ACL_TABLE_DEFINITION_NAME
    STAGE_FIELD = "stage"
    PRIORITY_FIELD = "priority"
    SIZE_FIELD = "size"
    MATCH_FIELD_ETHER_TYPE = "match/ether_type"
    MATCH_FIELD_ETHER_DST = "match/ether_dst"
    MATCH_FIELD_IS_IP = "match/is_ip"
    MATCH_FIELD_IS_IPV4 = "match/is_ipv4"
    MATCH_FIELD_IS_IPV6 = "match/is_ipv6"
    MATCH_FIELD_IS_ARP = "match/is_arp"
    MATCH_FIELD_SRC_IPV6_64BIT = "match/src_ipv6_64bit"
    MATCH_FIELD_ARP_TPA = "match/arp_tpa"
    ACTION_COPY_AND_SET_TC = "action/copy_and_set_tc"
    ACTION_PUNT_AND_SET_TC = "action/punt_and_set_tc"
    ACTION_SET_QOS_QUEUE = "action/qos_queue"
    METER_UNIT = "meter/unit"
    COUNTER_UNIT = "counter/unit"


class P4RtAclRuleWrapper(util.DBInterface):
    """Interface to interact with APP DB and ASIC DB tables for P4RT ACL entry object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_ACL_ENTRY"
    SAI_ATTR_TABLE_ID = "SAI_ACL_ENTRY_ATTR_TABLE_ID"
    SAI_ATTR_PRIORITY = "SAI_ACL_ENTRY_ATTR_PRIORITY"
    SAI_ATTR_ADMIN_STATE = "SAI_ACL_ENTRY_ATTR_ADMIN_STATE"
    SAI_ATTR_SET_POLICER = "SAI_ACL_ENTRY_ATTR_ACTION_SET_POLICER"
    SAI_ATTR_COUNTER = "SAI_ACL_ENTRY_ATTR_ACTION_COUNTER"
    SAI_ATTR_MATCH_ETHER_TYPE = "SAI_ACL_ENTRY_ATTR_FIELD_ETHER_TYPE"
    SAI_ATTR_MATCH_IP_TYPE = "SAI_ACL_ENTRY_ATTR_FIELD_ACL_IP_TYPE"
    SAI_ATTR_MATCH_DST_MAC = "SAI_ACL_ENTRY_ATTR_FIELD_DST_MAC"
    SAI_ATTR_MATCH_SRC_IPV6_WORD3 = "SAI_ACL_ENTRY_ATTR_FIELD_SRC_IPV6_WORD3"
    SAI_ATTR_MATCH_SRC_IPV6_WORD2 = "SAI_ACL_ENTRY_ATTR_FIELD_SRC_IPV6_WORD2"
    SAI_ATTR_MATCH_UDF_GROUP_MIN = "SAI_ACL_ENTRY_ATTR_USER_DEFINED_FIELD_GROUP_MIN"
    SAI_ATTR_MATCH_UDF_GROUP_1 = "SAI_ACL_ENTRY_ATTR_USER_DEFINED_FIELD_GROUP_1"
    SAI_ATTR_ACTION_PACKET_ACTION = "SAI_ACL_ENTRY_ATTR_ACTION_PACKET_ACTION"
    SAI_ATTR_ACTION_SET_TC = "SAI_ACL_ENTRY_ATTR_ACTION_SET_TC"
    SAI_ATTR_ACTION_SET_USER_TRAP_ID = "SAI_ACL_ENTRY_ATTR_ACTION_SET_USER_TRAP_ID"

    # table name in APP_DB and attribute fields
    APP_DB_TBL_NAME = swsscommon.APP_P4RT_TABLE_NAME
    ACTION = "action"
    METER_CIR = "meter/cir"
    METER_CBURST = "meter/cburst"
    METER_PIR = "meter/pir"
    METER_PBURST = "meter/pburst"


class P4RtAclCounterWrapper(util.DBInterface):
    """Interface to interact with APP DB and ASIC DB tables for P4RT ACL counter object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_ACL_COUNTER"
    SAI_ATTR_TABLE_ID = "SAI_ACL_COUNTER_ATTR_TABLE_ID"
    SAI_ATTR_ENABLE_BYTE_COUNT = "SAI_ACL_COUNTER_ATTR_ENABLE_BYTE_COUNT"
    SAI_ATTR_ENABLE_PACKET_COUNT = "SAI_ACL_COUNTER_ATTR_ENABLE_PACKET_COUNT"


class P4RtAclMeterWrapper(util.DBInterface):
    """Interface in ASIC DB tables for P4RT ACL policer object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_POLICER"
    SAI_ATTR_METER_TYPE = "SAI_POLICER_ATTR_METER_TYPE"
    SAI_ATTR_METER_MODE = "SAI_POLICER_ATTR_MODE"
    SAI_ATTR_METER_CBS = "SAI_POLICER_ATTR_CBS"
    SAI_ATTR_METER_CIR = "SAI_POLICER_ATTR_CIR"
    SAI_ATTR_METER_PBS = "SAI_POLICER_ATTR_PBS"
    SAI_ATTR_METER_PIR = "SAI_POLICER_ATTR_PIR"
    SAI_ATTR_GREEN_PACKET_ACTION = "SAI_POLICER_ATTR_GREEN_PACKET_ACTION"
    SAI_ATTR_RED_PACKET_ACTION = "SAI_POLICER_ATTR_RED_PACKET_ACTION"
    SAI_ATTR_YELLOW_PACKET_ACTION = "SAI_POLICER_ATTR_YELLOW_PACKET_ACTION"


class P4RtAclGroupWrapper(util.DBInterface):
    """Interface in ASIC DB tables for P4RT ACL group object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_ACL_TABLE_GROUP"
    SAI_ACL_TABLE_GROUP_ATTR_ACL_STAGE = "SAI_ACL_TABLE_GROUP_ATTR_ACL_STAGE"
    SAI_ACL_TABLE_GROUP_ATTR_TYPE = "SAI_ACL_TABLE_GROUP_ATTR_TYPE"
    SAI_ACL_TABLE_ATTR_ACL_BIND_POINT_TYPE_LIST = "SAI_ACL_TABLE_ATTR_ACL_BIND_POINT_TYPE_LIST"

    def get_group_oids_by_stage(self, stage):
        tbl = swsscommon.Table(self.asic_db, self.ASIC_DB_TBL_NAME)
        keys = tbl.getKeys()
        group_oids = []
        for key in keys:
            (status, fvs) = tbl.get(key)
            assert status == True
            for name, val in fvs:
                if name == self.SAI_ACL_TABLE_GROUP_ATTR_ACL_STAGE and val == stage:
                    group_oids.append(key)
                    break
        return group_oids


class P4RtAclGroupMemberWrapper(util.DBInterface):
    """Interface in ASIC DB tables for P4RT ACL group member object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_ACL_TABLE_GROUP_MEMBER"
    SAI_ACL_TABLE_GROUP_MEMBER_ATTR_ACL_TABLE_GROUP_ID = "SAI_ACL_TABLE_GROUP_MEMBER_ATTR_ACL_TABLE_GROUP_ID"
    SAI_ACL_TABLE_GROUP_MEMBER_ATTR_ACL_TABLE_ID = "SAI_ACL_TABLE_GROUP_MEMBER_ATTR_ACL_TABLE_ID"
    SAI_ACL_TABLE_GROUP_MEMBER_ATTR_PRIORITY = "SAI_ACL_TABLE_GROUP_MEMBER_ATTR_PRIORITY"


class P4RtUserDefinedTrapWrapper(util.DBInterface):
    """Interface in ASIC DB tables for SAI user defined trap object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_HOSTIF_USER_DEFINED_TRAP"
    SAI_HOSTIF_USER_DEFINED_TRAP_ATTR_TRAP_GROUP = "SAI_HOSTIF_USER_DEFINED_TRAP_ATTR_TRAP_GROUP"
    SAI_HOSTIF_USER_DEFINED_TRAP_ATTR_TYPE = "SAI_HOSTIF_USER_DEFINED_TRAP_ATTR_TYPE"


class P4RtTrapGroupWrapper(util.DBInterface):
    """Interface in APPL and ASIC DB tables for SAI trap group object."""

    # table name in APPL_DB and attribute fields
    APP_DB_TBL_NAME = "COPP_TABLE"
    TBL_NAME_PREFIX = "trap.group.cpu.queue."
    QUEUE = "queue"
    HOSTIF_NAME = "genetlink_name"
    HOSTIF_GENETLINK_MCGRP_NAME = "genetlink_mcgrp_name"

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_HOSTIF_TRAP_GROUP"
    SAI_HOSTIF_TRAP_GROUP_ATTR_QUEUE = "SAI_HOSTIF_TRAP_GROUP_ATTR_QUEUE"


class P4RtHostifWrapper(util.DBInterface):
    """Interface in ASIC DB tables for SAI hostif object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_HOSTIF"
    SAI_HOSTIF_ATTR_TYPE = "SAI_HOSTIF_ATTR_TYPE"
    SAI_HOSTIF_ATTR_NAME = "SAI_HOSTIF_ATTR_NAME"
    SAI_HOSTIF_ATTR_GENETLINK_MCGRP_NAME = "SAI_HOSTIF_ATTR_GENETLINK_MCGRP_NAME"


class P4RtHostifTableEntryWrapper(util.DBInterface):
    """Interface in ASIC DB tables for SAI hostif table entry object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_HOSTIF_TABLE_ENTRY"
    SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE = "SAI_HOSTIF_TABLE_ENTRY_ATTR_TYPE"
    SAI_HOSTIF_TABLE_ENTRY_ATTR_TRAP_ID = "SAI_HOSTIF_TABLE_ENTRY_ATTR_TRAP_ID"
    SAI_HOSTIF_TABLE_ENTRY_ATTR_CHANNEL_TYPE = "SAI_HOSTIF_TABLE_ENTRY_ATTR_CHANNEL_TYPE"
    SAI_HOSTIF_TABLE_ENTRY_ATTR_HOST_IF = "SAI_HOSTIF_TABLE_ENTRY_ATTR_HOST_IF"

class P4RtUdfGroupWrapper(util.DBInterface):
    """Interface in ASIC DB tables for SAI UDF Group object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_UDF_GROUP"
    SAI_UDF_GROUP_ATTR_TYPE = "SAI_UDF_GROUP_ATTR_TYPE"
    SAI_UDF_GROUP_ATTR_LENGTH = "SAI_UDF_GROUP_ATTR_LENGTH"

    SAI_UDF_GROUP_TYPE_GENERIC = "SAI_UDF_GROUP_TYPE_GENERIC"


class P4RtUdfMatchWrapper(util.DBInterface):
    """Interface in ASIC DB tables for SAI UDF Match object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_UDF_MATCH"


class P4RtUdfWrapper(util.DBInterface):
    """Interface in ASIC DB tables for SAI UDF object."""

    # table name in ASIC_DB and SAI constants
    ASIC_DB_TBL_NAME = "ASIC_STATE:SAI_OBJECT_TYPE_UDF"
    SAI_UDF_ATTR_MATCH_ID = "SAI_UDF_ATTR_MATCH_ID"
    SAI_UDF_ATTR_GROUP_ID = "SAI_UDF_ATTR_GROUP_ID"
    SAI_UDF_ATTR_BASE = "SAI_UDF_ATTR_BASE"
    SAI_UDF_ATTR_OFFSET = "SAI_UDF_ATTR_OFFSET"
