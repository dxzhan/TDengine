/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// clang-format off

#if 0
#undef TD_MSG_INFO_
#undef TD_MSG_NUMBER_
#undef TD_MSG_DICT_
#undef TD_MSG_SEG_CODE_
#endif

#if defined(TD_MSG_INFO_)

  #undef TD_NEW_MSG_SEG
  #undef TD_DEF_MSG_TYPE
  #undef TD_CLOSE_MSG_SEG
  #define TD_NEW_MSG_SEG(TYPE) "null",
  #define TD_DEF_MSG_TYPE(TYPE, MSG, REQ, RSP) MSG, MSG "-rsp",
  #define TD_CLOSE_MSG_SEG(TYPE)

  char *tMsgInfo[] = {

#elif defined(TD_MSG_RANGE_CODE_)

  #undef TD_NEW_MSG_SEG
  #undef TD_DEF_MSG_TYPE
  #undef TD_CLOSE_MSG_SEG
  #define TD_NEW_MSG_SEG(TYPE)
  #define TD_DEF_MSG_TYPE(TYPE, MSG, REQ, RSP)
  #define TD_CLOSE_MSG_SEG(TYPE) TYPE,
  int32_t tMsgRangeDict[] = {

#elif defined(TD_MSG_NUMBER_)

  #undef TD_NEW_MSG_SEG
  #undef TD_DEF_MSG_TYPE
  #undef TD_CLOSE_MSG_SEG
  #define TD_NEW_MSG_SEG(TYPE) TYPE##_NUM,
  #define TD_DEF_MSG_TYPE(TYPE, MSG, REQ, RSP) TYPE##_NUM, TYPE##_RSP_NUM,
  #define TD_CLOSE_MSG_SEG(TYPE)

  enum {

#elif defined(TD_MSG_DICT_)

  #undef TD_NEW_MSG_SEG
  #undef TD_DEF_MSG_TYPE
  #undef TD_CLOSE_MSG_SEG
  #define TD_NEW_MSG_SEG(TYPE) TYPE##_NUM,
  #define TD_DEF_MSG_TYPE(TYPE, MSG, REQ, RSP)
  #define TD_CLOSE_MSG_SEG(type)

  int32_t tMsgDict[] = {


#elif defined(TD_MSG_SEG_CODE_)

  #undef TD_NEW_MSG_SEG
  #undef TD_DEF_MSG_TYPE
  #undef TD_CLOSE_MSG_SEG
  #define TD_NEW_MSG_SEG(TYPE) TYPE##_SEG_CODE,
  #define TD_DEF_MSG_TYPE(TYPE, MSG, REQ, RSP)
  #define TD_CLOSE_MSG_SEG(TYPE)

  enum {
#else

  #undef TD_NEW_MSG_SEG
  #undef TD_DEF_MSG_TYPE
  #undef TD_CLOSE_MSG_SEG
  #define TD_NEW_MSG_SEG(TYPE) TYPE = ((TYPE##_SEG_CODE) << 8),
  #define TD_DEF_MSG_TYPE(TYPE, MSG, REQ, RSP) TYPE, TYPE##_RSP,
  #define TD_CLOSE_MSG_SEG(TYPE) TYPE,

  enum { // WARN: new msg should be appended to segment tail
#endif
  TD_NEW_MSG_SEG(TDMT_DND_MSG)    // 0<<8
  TD_DEF_MSG_TYPE(TDMT_DND_CREATE_MNODE, "dnode-create-mnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_DROP_MNODE, "dnode-drop-mnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_CREATE_QNODE, "dnode-create-qnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_DROP_QNODE, "dnode-drop-qnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_CREATE_SNODE, "dnode-create-snode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_DROP_SNODE, "dnode-drop-snode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_CREATE_BNODE, "dnode-create-bnode", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_DND_DROP_BNODE, "dnode-drop-bnode", NULL, NULL)     // no longer used
  TD_DEF_MSG_TYPE(TDMT_DND_CREATE_VNODE, "create-vnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_DROP_VNODE, "drop-vnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_SERVER_STATUS, "server-status", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_NET_TEST, "net-test", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_CONFIG_DNODE, "config-dnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_SYSTABLE_RETRIEVE, "dnode-retrieve", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_UNUSED_CODE, "dnd-unused", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_ALTER_MNODE_TYPE, "dnode-alter-mnode-type", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_ALTER_VNODE_TYPE, "dnode-alter-vnode-type", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_CHECK_VNODE_LEARNER_CATCHUP, "dnode-check-vnode-learner-catchup", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_CREATE_ENCRYPT_KEY, "create-encrypt-key", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_DND_MAX_MSG, "dnd-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_DND_MSG)

  TD_NEW_MSG_SEG(TDMT_MND_MSG)  // 1<<8
  TD_DEF_MSG_TYPE(TDMT_MND_CONNECT, "connect", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_ACCT, "create-acct", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_ACCT, "alter-acct", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_ACCT, "drop-acct", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_USER, "create-user", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_USER, "alter-user", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_USER, "drop-user", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_USER_AUTH, "get-user-auth", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_DNODE, "create-dnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CONFIG_DNODE, "config-dnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_DNODE, "drop-dnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_MNODE, "create-mnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_MNODE, "alter-mnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_MNODE, "drop-mnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_QNODE, "create-qnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_QNODE, "alter-qnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_QNODE, "drop-qnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_QNODE_LIST, "qnode-list", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DNODE_LIST, "dnode-list", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_SNODE, "create-snode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_SNODE, "alter-snode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_SNODE, "drop-snode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_BNODE, "create-bnode", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_BNODE, "alter-bnode", NULL, NULL)   // no longer used
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_BNODE, "drop-bnode", NULL, NULL)     // no longer used
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_DB, "create-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_DB, "drop-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_USE_DB, "use-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_DB, "alter-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_SYNC_DB, "sync-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_COMPACT_DB, "compact-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TRIM_DB, "trim-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_DB_CFG, "get-db-cfg", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_VGROUP_LIST, "vgroup-list", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_FUNC, "create-func", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_RETRIEVE_FUNC, "retrieve-func", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_FUNC, "drop-func", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_STB, "create-stb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_STB, "alter-stb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_STB, "drop-stb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TABLE_META, "table-meta", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_SMA, "create-sma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_SMA, "drop-sma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_STREAM, "create-stream", SCMCreateStreamReq, SCMCreateStreamRsp)
  TD_DEF_MSG_TYPE(TDMT_MND_ALTER_STREAM, "alter-stream", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_STREAM, "drop-stream", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_RECOVER_STREAM, "recover-stream", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_INDEX, "create-index", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_INDEX, "drop-index", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_INDEX, "get-index", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_TABLE_INDEX, "get-table-index", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_BATCH_META, "batch-meta", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TABLE_CFG, "table-cfg", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_CREATE_TOPIC, "create-topic", SMCreateTopicReq, SMCreateTopicRsp)
  TD_DEF_MSG_TYPE(TDMT_MND_UNUSED1, "unused", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_DROP_TOPIC, "drop-topic", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_SUBSCRIBE, "subscribe", SCMSubscribeReq, SCMSubscribeRsp)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_ASK_EP, "ask-ep", SMqAskEpReq, SMqAskEpRsp)
//  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_CONSUMER_LOST, "consumer-lost", SMqConsumerLostMsg, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_CONSUMER_RECOVER, "consumer-recover", SMqConsumerRecoverMsg, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_HB, "consumer-hb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_DO_REBALANCE, "do-rebalance", SMqDoRebalanceMsg, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_DROP_CGROUP, "drop-cgroup", SMqDropCGroupReq, SMqDropCGroupRsp)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_VG, "create-vg", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_TIMER, "tmq-tmr", SMTimerReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TELEM_TIMER, "telem-tmr", SMTimerReq, SMTimerReq)
  TD_DEF_MSG_TYPE(TDMT_MND_TRANS_TIMER, "trans-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TTL_TIMER, "ttl-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GRANT_HB_TIMER, "grant-hb-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_NODECHECK_TIMER, "node-check-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_KILL_TRANS, "kill-trans", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_KILL_QUERY, "kill-query", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_KILL_CONN, "kill-conn", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_HEARTBEAT, "heartbeat", SClientHbBatchReq, SClientHbBatchRsp)
  TD_DEF_MSG_TYPE(TDMT_MND_STATUS, "status", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_SHOW, "show", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_SYSTABLE_RETRIEVE, "mnd-retrieve", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GRANT, "grant", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_AUTH, "auth", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_APPLY_MSG, "mnode-apply", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_BALANCE_VGROUP, "balance-vgroup", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_MERGE_VGROUP, "merge-vgroup", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_REDISTRIBUTE_VGROUP, "redistribute-vgroup", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_SPLIT_VGROUP, "split-vgroup", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_SHOW_VARIABLES, "show-variables", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_SERVER_VERSION, "server-version", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_UPTIME_TIMER, "uptime-timer", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TMQ_LOST_CONSUMER_CLEAR, "lost-consumer-clear", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STREAM_HEARTBEAT, "stream-heartbeat", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_RETRIEVE_IP_WHITE, "retrieve-ip-white", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_USER_WHITELIST, "get-user-whitelist", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_NOTIFY, "notify", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_BALANCE_VGROUP_LEADER, "balance-vgroup-leader", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_RESTORE_DNODE, "restore-dnode", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_PAUSE_STREAM, "pause-stream", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_RESUME_STREAM, "resume-stream", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STREAM_UPDATE_CHKPT_EVT, "stream-update-chkpt-evt", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STREAM_BEGIN_CHECKPOINT, "stream-begin-checkpoint", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STREAM_CHKPT_REPORT, "stream-chkpt-report", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STREAM_NODECHANGE_CHECK, "stream-nodechange-check", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_TRIM_DB_TIMER, "trim-db-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GRANT_NOTIFY, "grant-notify", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_VIEW, "create-view", SCMCreateViewReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_VIEW, "drop-view", SCMDropViewReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_VIEW_META, "view-meta", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STATIS, "statis", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_KILL_COMPACT, "kill-compact", SKillCompactReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_COMPACT_TIMER, "compact-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STREAM_REQ_CHKPT, "stream-req-checkpoint", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CONFIG_CLUSTER, "config-cluster", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_ENCRYPT_KEY, "create-encrypt-key", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_S3MIGRATE_DB, "s3migrate-db", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_S3MIGRATE_DB_TIMER, "s3migrate-db-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_UNUSED2, "mnd-unused2", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_CREATE_TSMA, "create-tsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_TSMA, "drop-tsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_STB_DROP, "drop-stb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_TABLE_TSMA, "get-table-tsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_GET_TSMA, "get-tsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_DROP_TB_WITH_TSMA, "drop-tb-with-tsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_MAX_MSG, "mnd-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_MND_MSG)

  TD_NEW_MSG_SEG(TDMT_VND_MSG)  // 2<<8
  TD_DEF_MSG_TYPE(TDMT_VND_SUBMIT, "submit", SSubmitReq, SSubmitRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_CREATE_TABLE, "create-table", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ALTER_TABLE, "alter-table", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DROP_TABLE, "drop-table", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UPDATE_TAG_VAL, "update-tag-val", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TABLE_META, "vnode-table-meta", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TABLES_META, "vnode-tables-meta", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TABLE_CFG, "vnode-table-cfg", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_BATCH_META, "vnode-batch-meta", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_CREATE_STB, "vnode-create-stb", SVCreateStbReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ALTER_STB, "vnode-alter-stb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DROP_STB, "vnode-drop-stb", SVDropStbReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED1, "vnode-unused1", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED2, "vnode-unused2", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED3, "vnode-unused3", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED4, "vnode-unused4", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED5, "vnode-unused5", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED6, "vnode-unused6", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED7, "vnode-unused7", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED8, "vnode-unused8", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED9, "vnode-unused9", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED10, "vnode-unused10", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED11, "vnode-unused11", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED12, "vnode-unused12", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED13, "vnode-unused13", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED14, "vnode-unused14", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_UNUSED15, "vnode-unused15", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_CREATE_SMA, "vnode-create-sma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_CANCEL_SMA, "vnode-cancel-sma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DROP_SMA, "vnode-drop-sma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_SUBMIT_RSMA, "vnode-submit-rsma", SSubmitReq, SSubmitRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_FETCH_RSMA, "vnode-fetch-rsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_EXEC_RSMA, "vnode-exec-rsma", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DELETE, "delete-data", SVDeleteReq, SVDeleteRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_BATCH_DEL, "batch-delete", SBatchDeleteReq, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ALTER_CONFIG, "alter-config", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ALTER_REPLICA, "alter-replica", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ALTER_CONFIRM, "alter-confirm", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ALTER_HASHRANGE, "alter-hashrange", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_COMPACT, "vnode-compact", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DROP_TTL_TABLE, "vnode-drop-ttl-stb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TRIM, "vnode-trim", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_COMMIT, "vnode-commit", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_CREATE_INDEX, "vnode-create-index", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DROP_INDEX, "vnode-drop-index", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_DISABLE_WRITE, "vnode-disable-write", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_QUERY_COMPACT_PROGRESS, "vnode-query-compact-progress", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_KILL_COMPACT, "kill-compact", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_S3MIGRATE, "vnode-s3migrate", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ARB_HEARTBEAT, "vnode-arb-hb", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_ARB_CHECK_SYNC, "vnode-arb-check-sync", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_FETCH_TTL_EXPIRED_TBS, "vnode-fetch-ttl-expired-tbs", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_MAX_MSG, "vnd-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_VND_MSG)

  TD_NEW_MSG_SEG(TDMT_SCH_MSG)  // 3<<8
  TD_DEF_MSG_TYPE(TDMT_SCH_QUERY, "query", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_MERGE_QUERY, "merge-query", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_QUERY_CONTINUE, "query-continue", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_QUERY_HEARTBEAT, "query-heartbeat", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_FETCH, "fetch", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_MERGE_FETCH, "merge-fetch", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_CANCEL_TASK, "cancel-task", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_DROP_TASK, "drop-task", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_EXPLAIN, "explain", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_LINK_BROKEN, "link-broken", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_TASK_NOTIFY, "task-notify", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SCH_MAX_MSG, "sch-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_SCH_MSG)


  TD_NEW_MSG_SEG(TDMT_STREAM_MSG)   //4 << 8
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_DEPLOY, "stream-task-deploy", SStreamTaskDeployReq, SStreamTaskDeployRsp)  //1025 1026
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_DROP, "stream-task-drop", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_RUN, "stream-task-run", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_DISPATCH, "stream-task-dispatch", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_UPDATE_CHKPT, "stream-update-chkptinfo", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_RETRIEVE, "stream-retrieve", NULL, NULL)  //1035 1036
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_CHECKPOINT_READY, "stream-checkpoint-ready", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_REPORT_CHECKPOINT, "stream-report-checkpoint", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_RESTORE_CHECKPOINT, "stream-restore-checkpoint", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_PAUSE, "stream-task-pause", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_RESUME, "stream-task-resume", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_TASK_STOP, "stream-task-stop", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_UNUSED, "stream-unused", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_CREATE, "stream-create", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_DROP, "stream-drop", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_STREAM_RETRIEVE_TRIGGER, "stream-retri-trigger", NULL, NULL)

  TD_DEF_MSG_TYPE(TDMT_STREAM_MAX_MSG, "stream-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_STREAM_MSG)

  TD_NEW_MSG_SEG(TDMT_MON_MSG)  //5 << 8
  TD_DEF_MSG_TYPE(TDMT_MON_MAX_MSG, "monitor-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_MON_MSG)

  TD_NEW_MSG_SEG(TDMT_SYNC_MSG) //6 << 8
  TD_DEF_MSG_TYPE(TDMT_SYNC_TIMEOUT, "sync-timer", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_TIMEOUT_ELECTION, "sync-elect", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_PING_REPLY, "sync-ping-reply", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_SYNC_CLIENT_REQUEST, "sync-client-request", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_CLIENT_REQUEST_BATCH, "sync-client-request-batch", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_CLIENT_REQUEST_REPLY, "sync-client-request-reply", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_REQUEST_VOTE, "sync-request-vote", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_REQUEST_VOTE_REPLY, "sync-request-vote-reply", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_APPEND_ENTRIES, "sync-append-entries", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_APPEND_ENTRIES_BATCH, "sync-append-entries-batch", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_APPEND_ENTRIES_REPLY, "sync-append-entries-reply", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_NOOP, "sync-noop", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_UNKNOWN, "sync-unknown", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_COMMON_RESPONSE, "sync-common-response", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_APPLY_MSG, "sync-apply-msg", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_CONFIG_CHANGE, "sync-config-change", NULL, NULL)               // no longer used
  TD_DEF_MSG_TYPE(TDMT_SYNC_CONFIG_CHANGE_FINISH, "sync-config-change-finish", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_SYNC_SNAPSHOT_SEND, "sync-snapshot-send", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_SNAPSHOT_RSP, "sync-snapshot-rsp", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_LEADER_TRANSFER, "sync-leader-transfer", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_SET_MNODE_STANDBY, "set-mnode-standby", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_SYNC_SET_VNODE_STANDBY, "set-vnode-standby", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_SYNC_HEARTBEAT, "sync-heartbeat", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_HEARTBEAT_REPLY, "sync-heartbeat-reply", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_LOCAL_CMD, "sync-local-cmd", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_PREP_SNAPSHOT, "sync-prep-snapshot", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_PREP_SNAPSHOT_REPLY, "sync-prep-snapshot-reply", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_UNUSED_CODE, "sync-unused", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_FORCE_FOLLOWER, "sync-force-become-follower", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_SET_ASSIGNED_LEADER, "sync-set-assigned-leader", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_SYNC_MAX_MSG, "sync-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_SYNC_MSG)

  TD_NEW_MSG_SEG(TDMT_VND_STREAM_MSG) //7 << 8
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_SCAN_HISTORY, "vnode-stream-scan-history", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_CHECK_POINT_SOURCE, "vnode-stream-checkpoint-source", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_TASK_UPDATE, "vnode-stream-update", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_TASK_RESET, "vnode-stream-reset", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_TASK_CHECK, "vnode-stream-task-check", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_UNUSED, "vnd-stream-unused", NULL, NULL)

  TD_DEF_MSG_TYPE(TDMT_VND_GET_STREAM_PROGRESS, "vnd-stream-progress", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_STREAM_MAX_MSG, "vnd-stream-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_VND_STREAM_MSG)

  TD_NEW_MSG_SEG(TDMT_VND_TMQ_MSG)  //8 << 8
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_SUBSCRIBE, "vnode-tmq-subscribe", SMqRebVgReq, SMqRebVgRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_DELETE_SUB, "vnode-tmq-delete-sub", SMqVDeleteReq, SMqVDeleteRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_COMMIT_OFFSET, "vnode-tmq-commit-offset", STqOffset, STqOffset)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_SEEK, "vnode-tmq-seek", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_ADD_CHECKINFO, "vnode-tmq-add-checkinfo", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_DEL_CHECKINFO, "vnode-del-checkinfo", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_CONSUME, "vnode-tmq-consume", SMqPollReq, SMqDataBlkRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_CONSUME_PUSH, "vnode-tmq-consume-push", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_VG_WALINFO, "vnode-tmq-vg-walinfo", SMqPollReq, SMqDataBlkRsp)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_VG_COMMITTEDINFO, "vnode-tmq-committedinfo", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_VND_TMQ_MAX_MSG, "vnd-tmq-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_TMQ_MSG)

  TD_NEW_MSG_SEG(TDMT_MND_ARB_MSG)  //9 << 8
  TD_DEF_MSG_TYPE(TDMT_MND_ARB_HEARTBEAT_TIMER, "mnd-arb-hb-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ARB_CHECK_SYNC_TIMER, "mnd-arb-check-sync-tmr", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ARB_UPDATE_GROUP, "mnd-arb-update-group", NULL, NULL) // no longer used
  TD_DEF_MSG_TYPE(TDMT_MND_ARB_UPDATE_GROUP_BATCH, "mnd-arb-update-group-batch", NULL, NULL)
  TD_DEF_MSG_TYPE(TDMT_MND_ARB_MAX_MSG, "mnd-arb-max", NULL, NULL)
  TD_CLOSE_MSG_SEG(TDMT_END_ARB_MSG)

  TD_NEW_MSG_SEG(TDMT_MAX_MSG)  // msg end mark
  TD_CLOSE_MSG_SEG(TDMT_END_MAX_MSG)

  #if defined(TD_MSG_NUMBER_)
    TDMT_MAX
  #endif
};
