#include "libyarn_protocol.h"
#include "yarnsimulator.pb.h"
#include "rpc.pb.h"
#include <iostream>

using namespace std;

namespace libyarn
{

JobContext createJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext)
{
    string rpc_buffer;
    string tmp_buffer;

    CreateJobResponseProto create_job_req;
    JobContextProto* job = create_job_req.mutable_jobcontext();
    job->set_jobname(jobContext.jobName);
    job->set_queue(jobContext.queue);
    create_job_req.SerializeToString(&tmp_buffer);
    
    protobuf::socketrpc::Request request;
    request.set_service_name("YarnSimulatorService");
    request.set_method_name("createJob");
    request.set_request_proto(tmp_buffer);

    request.SerializeToString(&rpc_buffer);

    JobContext job = jobContext;
    return job;
}

JobContext finishJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext)
{
    JobContext job = jobContext;
    return job;
}

}
