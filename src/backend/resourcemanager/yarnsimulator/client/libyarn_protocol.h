#ifndef __LIB_YARN_PROTOCOL_H
#define __LIB_YARN_PROTOCOL_H

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

extern "C"
{

typedef enum {
    APPLICATION_CLIENT_PROTOCOL = 0,
    APPLICATION_MASTER_PROTOCOL = 1,
    CONTAINER_MANAGEMENT_PROTOCOL = 2,
    LIBYARN_PROTOCOL = 3
} yarn_protocol_type_t;


typedef struct {
  int caller_id;                     /* caller-id, assume user shouldn't access this */
  int socket_id;                     /* socket-id, assume user shouldn't access this */
  const char* protocol_name;         /* name of protocol, assume user shouldn't access this */
  int app_id;                        /* application-id */
  int app_attempt_id;                /* application-attempt-id */
  int64_t cluster_timestamp;         /* time stamp of the cluster */
  char* uuid;                        /* uuid buffer to RPC client */
  int uuid_len;                      /* length of uuid buffer */
  pthread_mutex_t lock;              /* lock object */
} hadoop_rpc_proxy_t;


typedef struct{
	char* jobId;
	char* jobName;
	char* queue;
	char* status;
}JobContext;

typedef struct{
	char* id;
	char* hostname;
	int memory;
	int cpu;
	int status;
}Resource;

typedef struct{
	char* groupId;
	int resource_num;
	Resource** resources;
}ResourceGroup;


enum NodeState{
  NEW = 1,
  RUNNING = 2,
  UNHEALTHY = 3,
  DECOMMISSIONED =4,
  LOST = 5,
  REBOOTED =6
};

typedef struct{
    char* hostname;
    char* state;
    char* rack;
    int container_num;
    char* healthReport;
    int cpu;
    int memory;
    long lastHealthReportTime;
}NodeReport;

typedef struct{
	NodeReport** nodes;
	int node_num;
}ClusterReport;

void sayHi();

// create rpc proxy with specified protocol_name and type, return NULL if failed
hadoop_rpc_proxy_t* create_new_yarn_rpc_proxy(yarn_protocol_type_t t);

// setup connection for this proxy with specified host and port, return 0 if succeed
int setup_connection(const hadoop_rpc_proxy_t* proxy, const char* host, int port);

JobContext createJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext);

JobContext finishJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext);

ResourceGroup allocateResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup);

ResourceGroup activeResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup);

ResourceGroup releaseResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup);

ClusterReport getClusterReport(hadoop_rpc_proxy_t* proxy, enum NodeState state);

}

#endif


