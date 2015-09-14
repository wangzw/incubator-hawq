#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdlib.h> 

#include "yarnsimulator_client.h"

YarnSimulatorClient::YarnSimulatorClient(const String& service_name)
{
    this->_service_name = service_name;
    const char* ip = getenv("YARN_SIMULATOR_IP");
    this->_yarn_ip = INVALID(ip) ? "127.0.0.1" : ip;   
    const char* port = getenv("YARN_SIMULATOR_PORT");
    this->_yarn_port = INVALID(port) ? 18080 : atoi(port);

    this->_sock = -1;
}

bool YarnSimulatorClient::init()
{
    this->_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sock < 0) {
        return false;
    }

    struct sockaddr_in svr_addr;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(this->_yarn_port);
    memset(&(svr_addr.sin_zero), 0, 8);
    svr_addr.sin_addr.s_addr = inet_addr(this->_yarn_ip.c_str());
    
    if (connect(this->_sock, (struct sockaddr*)&svr_addr, sizeof(svr_addr)) < 0) {
        return false; 
    }

    return true;
}
   
bool YarnSimulatorClient::process_request(const String& method, const String& request_proto_string, String& response_proto_string)
{
    String request_buffer;
    String recv_buffer;
    char buf;
    int ret = -1;
    
    protobuf::socketrpc::Request request;
    protobuf::socketrpc::Response response;
   
    // set request
    request.set_service_name(this->_service_name);
    request.set_method_name(method);
    request.set_request_proto(request_proto_string);
    if (!request.SerializeToString(&request_buffer)) {
        return false;
    }

    // send request
    if (send(this->_sock, (void*)request_buffer.c_str(), request_buffer.size(), 0) < 0) {
        return false;
    } else {
        shutdown(this->_sock, SHUT_WR);
    }
   
    // receive response
    while ((ret = recv(this->_sock, (void*)&buf, 1, 0)) > 0) {
        recv_buffer.append(1, buf);
    }

    if (ret < 0) {
        return false;
    } else {
        close(this->_sock);
        if (!response.ParseFromString(recv_buffer)) {
            return false;
        }
    }

    response_proto_string = response.response_proto();
    return true;
}
