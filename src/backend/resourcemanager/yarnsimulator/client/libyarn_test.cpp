#include <iostream>
#include <cstdlib>
#include <cstring>
#include "libyarn_protocol.h"
#include "yarnsimulator_utils.h"

using namespace std;

#define MAX_LEN 1024

void dumpJob(const JobContext& job)
{
    cout<<"------------------------------------------------"<<endl;
    cout<<"JobId:"<<job.jobId<<endl;
    cout<<"JobName:"<<job.jobName<<endl;
    cout<<"Queue:"<<job.queue<<endl;
    cout<<"Status:"<<job.status<<endl;
    cout<<"------------------------------------------------"<<endl;
}

void dumpResourceGroup(const ResourceGroup& rg)
{
    cout<<"------------------------------------------------"<<endl;
    cout<<"GroupId:"<<rg.groupId<<endl;
    cout<<"ResourceNum:"<<rg.resource_num<<endl;
    for (int i=0;i<rg.resource_num;i++) {
        cout<<"Resource "<<i<<" :"<<endl;
        cout<<"\tid="<<rg.resources[i]->id<<endl;;
        cout<<"\thostname="<<rg.resources[i]->hostname<<endl;;
        cout<<"\tmemory="<<rg.resources[i]->memory<<endl;;
        cout<<"\tcpu="<<rg.resources[i]->cpu<<endl;;
        cout<<"\tstatus="<<rg.resources[i]->status<<endl;;
    }
    cout<<"------------------------------------------------"<<endl;
}

void dumpClusterReport(const ClusterReport& cr)
{
    cout<<"------------------------------------------------"<<endl;
    cout<<"NodeNum:"<<cr.node_num<<endl;
    for (int i=0;i<cr.node_num;i++) {
        cout<<"NodeReport "<<i<<": "<<endl;
        cout<<"\thostname="<<cr.nodes[i]->hostname<<endl;
        cout<<"\tstate="<<cr.nodes[i]->state<<endl;
        cout<<"\track="<<cr.nodes[i]->rack<<endl;
        cout<<"\tcontainer_num="<<cr.nodes[i]->container_num<<endl;
        cout<<"\tmemory="<<cr.nodes[i]->memory<<endl;
        cout<<"\tcpu="<<cr.nodes[i]->cpu<<endl;
        cout<<"\thealthReport="<<cr.nodes[i]->healthReport<<endl;
        cout<<"\tlastHealthReportTime"<<cr.nodes[i]->lastHealthReportTime<<endl;
    }
    cout<<"------------------------------------------------"<<endl;
}

int main(int argc, char* argv[])
{
    LOG_INFO("hello world, %s", "ivan");

    JobContext job_req;
    JobContext job_res;
    job_req.jobName = "myjob";
    job_req.queue = "test_queue";

    job_res = createJob(NULL, job_req);
    dumpJob(job_res); 

    ResourceGroup resource_req;
    ResourceGroup resource_res;
    resource_req.groupId = "testgroup";
    resource_req.resource_num = 2;
    resource_req.resources = (Resource**)malloc(resource_req.resource_num * sizeof(Resource*));
    
    for (int i=0;i<2;i++) {
        Resource* resource = resource_req.resources[i] = (Resource*)malloc(sizeof(Resource));
        INIT(resource_req.resources[i]);
        resource->memory = 1000;
        resource->cpu = i + 1;
    } 
    
    resource_res = allocateResources(NULL, job_res.jobId, resource_req);
    dumpResourceGroup(resource_res);

    resource_res = activeResources(NULL, job_res.jobId, resource_res);
    dumpResourceGroup(resource_res);
    
    resource_res = releaseResources(NULL, job_res.jobId, resource_res);
    dumpResourceGroup(resource_res);

    ClusterReport report = getClusterReport(NULL, NEW);
    dumpClusterReport(report);
    return 0;
}
