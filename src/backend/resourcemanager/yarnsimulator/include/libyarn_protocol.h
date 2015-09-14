#include "yarn_service_protos.pb-c.h"
#include "yarn_protos.pb-c.h"
#include "libyarn_protos.pb-c.h"
#include "hadoop_rpc_utils.h"

#ifndef _LIB_YARN_PROTOCOL_H
#define _LIB_YARN_PROTOCOL_H

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
    int memory;
    int cpu;
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


#endif


