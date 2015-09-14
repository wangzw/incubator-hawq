#ifndef __YANR_SIMULATOR_CLIENT_H__
#define __YANR_SIMULATOR_CLIENT_H__

#include "rpc.pb.h"
#include "yarnsimulator_utils.h"

class YarnSimulatorClient
{
public:
    YarnSimulatorClient(const String& service_name);
    bool init(); 
    bool process_request(const String& method, const String& request_proto_string, String& response_proto_string);

    void set_service_name(const String& service_name) {
        this->_service_name = service_name;
    }

private:
    String _service_name;
    String _yarn_ip;
    int _yarn_port;
    int _sock;
};


#endif
