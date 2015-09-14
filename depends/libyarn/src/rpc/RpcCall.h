/********************************************************************
 * Copyright (c) 2014, Pivotal Inc.
 * All rights reserved.
 *
 * Author: Zhanwei Wang
 ********************************************************************/
#ifndef _HDFS_LIBHDFS3_RPC_RPCCALL_H_
#define _HDFS_LIBHDFS3_RPC_RPCCALL_H_

#include "google/protobuf/message.h"

namespace Yarn {
namespace Internal {

class RpcCall {
public:
    RpcCall(bool idemp, std::string n, google::protobuf::Message * req,
            google::protobuf::Message * resp) :
        idempotent(idemp), name(n), request(req), response(resp) {
    }

    bool isIdempotent() const {
        return idempotent;
    }

    const char * getName() const {
        return name.c_str();
    }

    void setIdempotent(bool idempotent) {
        this->idempotent = idempotent;
    }

    void setName(const std::string & name) {
        this->name = name;
    }

    google::protobuf::Message * getRequest() {
        return request;
    }

    void setRequest(google::protobuf::Message * request) {
        this->request = request;
    }

    google::protobuf::Message * getResponse() {
        return response;
    }

    void setResponse(google::protobuf::Message * response) {
        this->response = response;
    }

private:
    bool idempotent;
    std::string name;
    google::protobuf::Message * request;
    google::protobuf::Message * response;
};

}
}
#endif /* _HDFS_LIBHDFS3_RPC_RPCCALL_H_ */
