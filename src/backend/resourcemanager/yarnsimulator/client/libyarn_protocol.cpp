#include "rpc.pb.h"
#include "libyarn_protocol.h"
#include "yarnsimulator.pb.h"
#include "yarnsimulator_client.h"
#include <iostream>
#include <sys/types.h>

#define MAX_LEN 1024

hadoop_rpc_proxy_t* create_new_yarn_rpc_proxy(yarn_protocol_type_t t)
{
    hadoop_rpc_proxy_t* proxy = (hadoop_rpc_proxy_t*)malloc(sizeof(hadoop_rpc_proxy_t));
    if (INVALID(proxy)) {
        return NULL;
    } else {
        INIT(proxy);
        return proxy;
    }
}

int setup_connection(const hadoop_rpc_proxy_t* proxy, const char* host, int port)
{
    return 0;
}

JobContext createJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext)
{
    JobContext job_res;
    INIT(&job_res);

    // check params
    if (INVALID(jobContext.queue) || INVALID(jobContext.jobName)) {
        LOG_WARN("create job invalid request"); 
        return job_res;
    }
    
    // init response
    job_res.jobId = (char*)malloc(MAX_LEN);
    job_res.jobName = (char*)malloc(MAX_LEN); 
    job_res.queue = (char*)malloc(MAX_LEN); 
    job_res.status = (char*)malloc(MAX_LEN); 
    strcpy(job_res.jobName, jobContext.jobName);
    strcpy(job_res.queue, jobContext.queue);

    // init yarn client
    YarnSimulatorClient client("YarnSimulatorService");
    if (!client.init()) {
        LOG_WARN("client init failed");
        return job_res;
    }

    // process request
    String create_job_buffer;    
    yarnsimulator::CreateJobRequestProto create_job_req;
    yarnsimulator::JobContextProto* job = create_job_req.mutable_jobcontext();
    job->set_jobname(jobContext.jobName);
    job->set_queue(jobContext.queue);
    create_job_req.SerializeToString(&create_job_buffer);
    
    String create_job_res_buffer;
    if (!client.process_request("createJob", create_job_buffer, create_job_res_buffer)) {
        LOG_WARN("client process request failed");
        return job_res;
    }
   
    // process response
    yarnsimulator::CreateJobResponseProto create_job_res;
    if (!create_job_res.ParseFromString(create_job_res_buffer)) {
        LOG_WARN("parse response CreateJobResponse error");
        return job_res;
    }
    const yarnsimulator::JobContextProto& rjc = create_job_res.jobcontext();
    strcpy(job_res.jobId, rjc.jobid().c_str());
    strcpy(job_res.status, rjc.status().c_str());

    return job_res;
}

JobContext finishJob(hadoop_rpc_proxy_t* proxy, JobContext jobContext)
{
    JobContext job = jobContext;
    return job;
}

ResourceGroup allocateResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup)
{
    ResourceGroup resource_group_res;
    INIT(&resource_group_res);

    // check params
    if (INVALID(jobId) || INVALID(resourceGroup.groupId)) {
        LOG_WARN("allocate resources invalid request");
        return resource_group_res;
    }
   
    // init response
    resource_group_res.groupId = (char*)malloc(MAX_LEN);
    resource_group_res.resource_num = 0;
    strcpy(resource_group_res.groupId, resourceGroup.groupId);

    // init yarn client
    YarnSimulatorClient client("YarnSimulatorService");
    if (!client.init()) {
        LOG_WARN("client init failed");
        return resource_group_res;
    }

    // process request
    String request_buffer;
    yarnsimulator::AllocateResourcesRequestProto allocate_resource_request;
    allocate_resource_request.set_jobid(jobId);
    yarnsimulator::ResourceGroupProto* resource_group_req = allocate_resource_request.mutable_resourcegroup();
    resource_group_req->set_groupid(resourceGroup.groupId);
    for (int i=0;i<resourceGroup.resource_num;i++) {
        Resource* resource = resourceGroup.resources[i];
        yarnsimulator::ResourceProto* resource_proto = resource_group_req->add_resources();
        if (resource->hostname) { 
            resource_proto->set_hostname(resource->hostname);
        }
        resource_proto->set_memory(resource->memory);
        resource_proto->set_cpu(resource->cpu);
    }
    allocate_resource_request.SerializeToString(&request_buffer);

    String allocate_resource_response;
    if (!client.process_request("allocateResources", request_buffer, allocate_resource_response)) {
        LOG_WARN("client process request failed");
        return resource_group_res;
    }

    // process response
    yarnsimulator::AllocateResourcesResponseProto allocate_resource_res;
    if (!allocate_resource_res.ParseFromString(allocate_resource_response)) {
        LOG_WARN("parse response AllocateResourcesResponseProto error");
        return resource_group_res;
    }
        
    const yarnsimulator::ResourceGroupProto& rrg = allocate_resource_res.resourcegroup();
    resource_group_res.resource_num = rrg.resources_size();
    resource_group_res.resources = (Resource**)malloc(rrg.resources_size() * sizeof(Resource*));
    for (int i=0;i<rrg.resources_size();i++) {
        Resource* resource = resource_group_res.resources[i] = (Resource*)malloc(sizeof(Resource));
        resource->id = (char*)malloc(MAX_LEN);
        strcpy(resource->id, rrg.resources(i).id().c_str());
        resource->hostname = (char*)malloc(MAX_LEN);
        strcpy(resource->hostname, rrg.resources(i).hostname().c_str());
        resource->memory = rrg.resources(i).memory();
        resource->cpu = rrg.resources(i).cpu();
        resource->status = rrg.resources(i).status();
    }

    return resource_group_res;
}

ResourceGroup activeResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup)
{
    ResourceGroup resource_group_res;
    INIT(&resource_group_res);

    // check params
    if (INVALID(jobId) || INVALID(resourceGroup.groupId)) {
        LOG_WARN("active resources invalid request");
        return resource_group_res;
    }
   
    // init response
    resource_group_res.groupId = (char*)malloc(MAX_LEN);
    resource_group_res.resource_num = 0;
    strcpy(resource_group_res.groupId, resourceGroup.groupId);

    // init yarn client
    YarnSimulatorClient client("YarnSimulatorService");
    if (!client.init()) {
        LOG_WARN("client init failed");
        return resource_group_res;
    }

    // process request
    String request_buffer;
    yarnsimulator::ActiveResourcesRequestProto active_resource_request;
    active_resource_request.set_jobid(jobId);
    yarnsimulator::ResourceGroupProto* resource_group_req = active_resource_request.mutable_resourcegroup();
    resource_group_req->set_groupid(resourceGroup.groupId);
    for (int i=0;i<resourceGroup.resource_num;i++) {
        Resource* resource = resourceGroup.resources[i];
        yarnsimulator::ResourceProto* resource_proto = resource_group_req->add_resources();
        resource_proto->set_hostname(resource->hostname);
        resource_proto->set_memory(resource->memory);
        resource_proto->set_cpu(resource->cpu);
    }
    active_resource_request.SerializeToString(&request_buffer);

    String active_resource_response;
    if (!client.process_request("activeResources", request_buffer, active_resource_response)) {
        LOG_WARN("client process request failed");
        return resource_group_res;
    }

    // process response
    yarnsimulator::ActiveResourcesResponseProto active_resource_res;
    if (!active_resource_res.ParseFromString(active_resource_response)) {
        LOG_WARN("parse response ActiveResourcesResponseProto error");
        return resource_group_res;
    }
        
    const yarnsimulator::ResourceGroupProto& rrg = active_resource_res.resourcegroup();
    resource_group_res.resource_num = rrg.resources_size();
    resource_group_res.resources = (Resource**)malloc(rrg.resources_size() * sizeof(Resource*));
    for (int i=0;i<rrg.resources_size();i++) {
        Resource* resource = resource_group_res.resources[i] = (Resource*)malloc(sizeof(Resource));
        resource->id = (char*)malloc(MAX_LEN);
        strcpy(resource->id, rrg.resources(i).id().c_str());
        resource->hostname = (char*)malloc(MAX_LEN);
        strcpy(resource->hostname, rrg.resources(i).hostname().c_str());
        resource->memory = rrg.resources(i).memory();
        resource->cpu = rrg.resources(i).cpu();
        resource->status = rrg.resources(i).status();
    }

    return resource_group_res;

}

ResourceGroup releaseResources(hadoop_rpc_proxy_t* proxy, char* jobId, ResourceGroup resourceGroup)
{
    ResourceGroup resource_group_res;
    INIT(&resource_group_res);

    // check params
    if (INVALID(jobId) || INVALID(resourceGroup.groupId)) {
        LOG_WARN("release resources invalid request");
        return resource_group_res;
    }
   
    // init response
    resource_group_res.groupId = (char*)malloc(MAX_LEN);
    resource_group_res.resource_num = 0;
    strcpy(resource_group_res.groupId, resourceGroup.groupId);

    // init yarn client
    YarnSimulatorClient client("YarnSimulatorService");
    if (!client.init()) {
        LOG_WARN("client init failed");
        return resource_group_res;
    }

    // process request
    String request_buffer;
    yarnsimulator::ActiveResourcesRequestProto release_resource_request;
    release_resource_request.set_jobid(jobId);
    yarnsimulator::ResourceGroupProto* resource_group_req = release_resource_request.mutable_resourcegroup();
    resource_group_req->set_groupid(resourceGroup.groupId);
    for (int i=0;i<resourceGroup.resource_num;i++) {
        Resource* resource = resourceGroup.resources[i];
        yarnsimulator::ResourceProto* resource_proto = resource_group_req->add_resources();
        resource_proto->set_hostname(resource->hostname);
        resource_proto->set_memory(resource->memory);
        resource_proto->set_cpu(resource->cpu);
    }
    release_resource_request.SerializeToString(&request_buffer);

    String release_resource_response;
    if (!client.process_request("releaseResources", request_buffer, release_resource_response)) {
        LOG_WARN("client process request failed");
        return resource_group_res;
    }

    // process response
    yarnsimulator::ActiveResourcesResponseProto release_resource_res;
    if (!release_resource_res.ParseFromString(release_resource_response)) {
        LOG_WARN("parse response ReleaseResourcesResponseProto error");
        return resource_group_res;
    }
        
    const yarnsimulator::ResourceGroupProto& rrg = release_resource_res.resourcegroup();
    resource_group_res.resource_num = rrg.resources_size();
    resource_group_res.resources = (Resource**)malloc(rrg.resources_size() * sizeof(Resource*));
    for (int i=0;i<rrg.resources_size();i++) {
        Resource* resource = resource_group_res.resources[i] = (Resource*)malloc(sizeof(Resource));
        resource->id = (char*)malloc(MAX_LEN);
        strcpy(resource->id, rrg.resources(i).id().c_str());
        resource->hostname = (char*)malloc(MAX_LEN);
        strcpy(resource->hostname, rrg.resources(i).hostname().c_str());
        resource->memory = rrg.resources(i).memory();
        resource->cpu = rrg.resources(i).cpu();
        resource->status = rrg.resources(i).status();
    }

    return resource_group_res;
}


ClusterReport getClusterReport(hadoop_rpc_proxy_t* proxy, enum NodeState state)
{
    ClusterReport report;
    INIT(&report);

    // check params

    // init response

    // init yarn client
    YarnSimulatorClient client("YarnSimulatorService");
    if (!client.init()) {
        LOG_WARN("client init failed");
        return report;
    }
  
    // process request
    String request_buffer;
    yarnsimulator::GetClusterReportRequestProto get_report_request;
    get_report_request.set_state(yarnsimulator::NEW);
    get_report_request.SerializeToString(&request_buffer);

    String get_report_response;
    if (!client.process_request("getClusterReport", request_buffer, get_report_response)) {
        LOG_WARN("client process request failed");
        return report;
    }

    // process response
    yarnsimulator::GetClusterReportResponseProto get_report_res;
    if (!get_report_res.ParseFromString(get_report_response)) {
        LOG_WARN("parse response GetClusterReportResponseProto error");
        return report;
    }
    
    const yarnsimulator::ClusterReportProto& rcr = get_report_res.report();
    report.node_num = rcr.nodes_size();
    report.nodes = (NodeReport**)malloc(rcr.nodes_size() * sizeof(NodeReport*));
    for (int i=0;i<rcr.nodes_size();i++) {
        NodeReport* node_report = report.nodes[i] = (NodeReport*)malloc(sizeof(NodeReport));
        node_report->hostname = (char*)malloc(MAX_LEN);
        strcpy(node_report->hostname, rcr.nodes(i).hostname().c_str());
        node_report->state = (char*)malloc(MAX_LEN);
        strcpy(node_report->state, rcr.nodes(i).state().c_str());
        node_report->rack = (char*)malloc(MAX_LEN);
        strcpy(node_report->rack , rcr.nodes(i).rack().c_str());
        node_report->container_num = rcr.nodes(i).container_num();
        node_report->memory = rcr.nodes(i).memory();
        node_report->cpu = rcr.nodes(i).cpu();
        node_report->healthReport = (char*)malloc(MAX_LEN);
        strcpy(node_report->healthReport , rcr.nodes(i).healthreport().c_str());
        node_report->lastHealthReportTime = rcr.nodes(i).lasthealthreporttime();
    }

    return report;
}
