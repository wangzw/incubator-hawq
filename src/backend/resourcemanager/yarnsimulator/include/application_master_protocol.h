#include "yarn_service_protos.pb-c.h"
#include "yarn_protos.pb-c.h"
#include "libyarn_protos.pb-c.h"
#include "hadoop_rpc_utils.h"

#ifndef APPLICATION_MASTER_PROTOCOL_H_
#define APPLICATION_MASTER_PROTOCOL_H_


Hadoop__Yarn__RegisterApplicationMasterResponseProto* registerApplicationMaster(hadoop_rpc_proxy_t* proxy, char* host,
		int rpc_port, char* tracking_url);


#endif /* APPLICATION_MASTER_PROTOCOL_H_ */
