#ifndef _HD_CLIENT_HADOOP_RPC_CONSTANTS_H
#define _HD_CLIENT_HADOOP_RPC_CONSTANTS_H

/* protocols */
#define CLIENT_RM_PROTOCOL_NAME "org.apache.hadoop.yarn.api.ApplicationClientProtocolPB"
#define AM_RM_PROTOCOL_NAME "org.apache.hadoop.yarn.api.ApplicationMasterProtocolPB"
#define CONTAINER_MANAGER_PROTOCOL_NAME "org.apache.hadoop.yarn.api.ContainerManagementProtocolPB"

/* method names */
#define GET_NEW_APPLICATION_METHOD_NAME "getNewApplication"
#define REGISTER_APPLICATION_MASTER_METHOD_NAME "registerApplicationMaster"
#define ALLOCATE_RESOURCE_METHOD_NAME "allocate"
#define FINISH_APPLICATION_MASTER_METHOD_NAME "finishApplicationMaster"
#define START_CONTAINER_METHOD_NAME "startContainer"
#define GET_CONTAINER_STATUS_METHOD_NAME "getContainerStatus"

#define APP_ID_ENV_KEY "APP_ID_ENV"
#define CLUSTER_TIMESTAMP_ENV_KEY "CLUSTER_TIMESTAMP_ENV"
#define DEFAULT_LOCALRESOURCE_SERIALIZED_FILENAME "hamster_localresource_pb"

#define APACHE_HADOOP_202_VER "2.0.2-alpha"
#define APACHE_HADOOP_203_VER "2.0.3-alpha"

#endif
