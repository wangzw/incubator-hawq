#include "yarn_service_protos.pb-c.h"
#include "yarn_protos.pb-c.h"

#ifndef _LIB_YARN_APPLICATION_CLIENT_H
#define _LIB_YARN_APPLICATION_CLIENT_H

Hadoop__Yarn__GetNewApplicationResponseProto* getNewApplication(hadoop_rpc_proxy_t* proxy);

#endif
