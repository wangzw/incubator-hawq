#include <iostream>
#include <sstream>
#include "rpc.pb.h"
#include "yarnsimulator.pb.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <pthread.h>

#include "libyarn_protocol.h"

using namespace google::protobuf::io;
using namespace protobuf::socketrpc;
using namespace std;

pthread_t tid;
int hsock;

typedef struct _thread_data
{
    string tmpbuf;
    string buffer;
    Request  request;
    Response response;
} thread_data;

static void* rpc_thread_func(void *arg)
{
    thread_data* data = (thread_data*)arg;
    Request& req = data->request;
    req.SerializeToString(&data->buffer);

    int host_port= 18080;
    char* host_name="127.0.0.1";
    struct sockaddr_in my_addr;

    hsock = socket(AF_INET, SOCK_STREAM, 0);
    int flag = 1; 
    setsockopt(hsock, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int));
    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(host_port);

    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = inet_addr(host_name);

    if (connect( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        cout<<"connect error"<<endl;
        return NULL;
    } else {
        cout<<"connect ok"<<endl;
    }

    if (send(hsock, (void *)data->buffer.c_str(), data->buffer.size(), 0) < 0) {
        cout<<"send error"<<endl;
        return NULL;
    } else {
        cout<<"send ok"<<endl;
    }
   
    shutdown(hsock, SHUT_WR);

    return NULL;
}



int main(int argv, char** argc)
{
    thread_data* data = new thread_data;
    
    data->request.set_service_name("YarnSimulatorService");
    data->request.set_method_name("createJob");

    CreateJobRequestProto create_job_req;
    JobContextProto* job = create_job_req.mutable_jobcontext(); 
    job->set_jobname("myjob");
    job->set_queue("test_queue1");
    create_job_req.SerializeToString(&data->tmpbuf);
    data->request.set_request_proto(data->tmpbuf);

    rpc_thread_func((void*)data);
    /*
    int ret = pthread_create(&tid, NULL, rpc_thread_func, (void*)data);
    if (ret != 0) {
        cout<<"pthread_create error"<<endl;
        return -1;
    } else {
        cout<<"pthread_create ok"<<endl;
    }

    pthread_join(tid, NULL);
    */

    string recv_string;
    char buf ;
    int recv_size = 0;
    int total_size = 0;
    char recv_buffer[1024];
    memset(recv_buffer, 0, 1024);

    while (recv_size = recv(hsock, (void*)&buf, 1, 0) > 0) {
        recv_buffer[total_size] = buf;
        total_size += recv_size;
    }
    
    recv_string = recv_buffer;
    
    if ( recv_size < 0) {
        cout<<"recv error"<<endl;
        return -1;
    } else {
        cout<<"recv ok, total : "<<total_size<<", "<<recv_string.size()<<endl;
    }
    

    Response response;
    int ret = response.ParseFromString(recv_string);
    cout<<"response ret : "<<ret<<endl;
    string create_job_string = response.response_proto();
    CreateJobResponseProto create_job_res;
    ret = create_job_res.ParseFromString(create_job_string);
    cout<<"create job response ret : "<<ret<<endl;
    const JobContextProto& jobres = create_job_res.jobcontext();
    cout<<jobres.jobid()<<", "<<jobres.jobname()<<", "<<jobres.queue()<<", "<<jobres.status()<<endl;

    close(hsock);

    return 0;
}
