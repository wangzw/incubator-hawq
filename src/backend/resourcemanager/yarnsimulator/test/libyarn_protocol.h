#ifndef _TEST_LIB_YARN_PROTOCOL_H
#define _TEST_LIB_YARN_PROTOCOL_H

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

namespace libyarn
{

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
	long lastHealthReportTime;
}NodeReport;

typedef struct{
	NodeReport** nodes;
	int node_num;
}ClusterReport;

void sayHi();

JobContext createJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext);

JobContext finishJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext);

ResourceGroup allocateResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup);

ResourceGroup activeResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup);

ResourceGroup releaseResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup);

ClusterReport getClusterReport(hadoop_rpc_proxy_t* proxy, enum NodeState state);

}
#endif


