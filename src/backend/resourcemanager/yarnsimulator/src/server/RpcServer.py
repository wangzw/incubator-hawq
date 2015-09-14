import proto.yarnsimulator_pb2 as yarnproto
import time
import logging

logger = logging.getLogger('YarnSimulator')

class YarnSimulatorService(yarnproto.YarnSimulatorService):
    def __init__(self, cluster_info, resource_tracker):
        self.cluster = cluster_info
        self.tracker = resource_tracker

    def createJob(self, controller, request, done):
        logger.info('RPC createJob [REQ] ' + str(request))
       
        response = yarnproto.CreateJobResponseProto()
        
        queue = request.jobContext.queue
        job_name = request.jobContext.jobName
        
        response.jobContext.jobName = job_name
        response.jobContext.queue = queue
       
        # check request
        if not queue or not job_name:
            logger.warn('RPC createJob failed, invalid request. [REQ] + ' + str(request))
            response.jobContext.status = 'FAIL, invalid request'
        else:
            logger.debug('RPC createJob check request PASS')
            if not self.tracker.existQueue(queue):
                logger.warn('RPC createJob failed. invalid queue. [REQ] ' + str(request))
                response.jobContext.status = 'FAIL, invalid request'
            else:   
                job_id = self.tracker.genGlobalJobId()
                response.jobContext.jobId = job_id
                response.jobContext.status = 'SUCCESS'
                self.tracker.addJobInfo(queue, job_id, job_name)
        
        logger.info('RPC createJob [RES] ' + str(response))

        done.run(response)

    def finishJob(self, controller, request, done):
        logger.info('RPC finishJob [REQ] ' + str(request))
        
        response = yarnproto.FinishJobResponseProto()
        
        job_id = request.jobContext.jobId

        response.jobContext.jobId = job_id
       
        # check request
        if not job_id:
            logger.warn('RPC finishJob failed, invalid request. [REQ] + ' + str(request))
            response.jobContext.status = 'FAIL, invalid request'
        else:
            logger.debug('RPC finishJob check request PASS')
            if not self.tracker.existJob(job_id):
                logger.warn('RPC finishJob failed. invalid job. [REQ] ' + str(request))
                response.jobContext.status = 'FAIL, invalid request'
            else:
                (queue, jobname) = self.tracker.getJobInfo(job_id)
                response.jobContext.jobName = jobname
                response.jobContext.queue = queue
                response.jobContext.status = 'SUCCESS'
                self.tracker.removeJobInfo(job_id)
        
        logger.info('RPC finishJob [RES] ' + str(response))
        
        done.run(response)

    def allocateResources(self, controller, request, done):
        logger.info('RPC allocateResources [REQ] ' + str(request))
       
        job_id = request.jobId
        group_id = request.resourceGroup.groupId
        resources = []
        for resource in request.resourceGroup.resources:
            resources.append((resource.hostname, resource.memory, resource.cpu))

        response = yarnproto.AllocateResourcesResponseProto()
        response.resourceGroup.groupId = group_id 
       
        # check request
        if not job_id or not group_id:
            logger.warn('RPC allocateResources failed, invalid request. [REQ] + ' + str(request))
        else:
            logger.debug('RPC allocateResources check request PASS')
            if not self.tracker.existJob(job_id) or self.tracker.existResourceGroup(job_id, group_id):
                logger.warn('RPC allocateResources failed. invalid job or group. [REQ] ' + str(request))
            else:
                result = self.cluster.allocateResource(resources)
                if not result:
                    logger.warn('RPC cluster allocateResources failed. [REQ] ' + str(request))
                else:
                    for resource in result:
                        id, hostname, memory, cpu, status = resource
                        resource_response = response.resourceGroup.resources.add()
                        resource_response.id = id
                        resource_response.hostname = hostname
                        resource_response.memory = memory
                        resource_response.cpu = cpu
                        resource_response.status = status
                    self.tracker.addResourceInfo(job_id, group_id, result)

        logger.info('RPC allocateResources [RES] ' + str(response))

        done.run(response)

    def activeResources(self, controller, request, done):
        logger.info('RPC activeResources [REQ] ' + str(request))
 
        response = yarnproto.ActiveResourcesResponseProto()
        
        invalid_response = yarnproto.ActiveResourcesResponseProto()
        self.initInvalidResourceResponse(invalid_response, request.resourceGroup)

        job_id = request.jobId
        group_id = request.resourceGroup.groupId
        
        response.resourceGroup.groupId = group_id

        # check request
        if not job_id or not group_id:
            logger.warn('RPC activeResources failed, invalid request. [REQ] + ' + str(request))
            return invalid_response
        else:
            logger.debug('RPC activeResources check request PASS')
            if not self.tracker.existResourceGroup(job_id, group_id): 
                logger.warn('RPC activeResources failed. invalid job or group. [REQ] ' + str(request))
                return invalid_response
            else:
                resources = self.tracker.getResourceGroup(job_id, group_id)
                result = self.cluster.activeResource(resources)
                if not result:
                    logger.warn('RPC cluster activeResources failed. [REQ] ' + str(request))
                    return invalid_response
                else:
                    for resource in result:
                        id, hostname, memory, cpu, status = resource
                        resource_response = response.resourceGroup.resources.add()
                        resource_response.id = id
                        resource_response.hostname = hostname
                        resource_response.memory = memory
                        resource_response.cpu = cpu
                        resource_response.status = status

        logger.info('RPC activeResources [RES] ' + str(response))
        
        done.run(response)

    def releaseResources(self, controller, request, done):
        logger.info('RPC releaseResources [REQ] ' + str(request))
       
        response = yarnproto.ReleaseResourcesResponseProto()
        
        invalid_response = yarnproto.ReleaseResourcesResponseProto()
        self.initInvalidResourceResponse(invalid_response, request.resourceGroup)

        job_id = request.jobId
        group_id = request.resourceGroup.groupId
        
        response.resourceGroup.groupId = group_id

        # check request
        if not job_id or not group_id:
            logger.warn('RPC releaseResources failed, invalid request. [REQ] + ' + str(request))
            return invalid_response
        else:
            logger.debug('RPC releaseResources check request PASS')
            if not self.tracker.existResourceGroup(job_id, group_id): 
                logger.warn('RPC releaseResources failed. invalid job or group. [REQ] ' + str(request))
                return invalid_response
            else:
                resources = self.tracker.getResourceGroup(job_id, group_id)
                result = self.cluster.releaseResource(resources)
                if not result:
                    logger.warn('RPC cluster releaseResources failed. [REQ] ' + str(request))
                    return invalid_response
                else:
                    for resource in result:
                        id, hostname, memory, cpu, status = resource
                        resource_response = response.resourceGroup.resources.add()
                        resource_response.id = id
                        resource_response.hostname = hostname
                        resource_response.memory = memory
                        resource_response.cpu = cpu
                        resource_response.status = status

        logger.info('RPC releaseResources [RES] ' + str(response))

        self.tracker.removeResourceInfo(job_id, group_id, result)
        
        done.run(response)

    def getClusterReport(self, controller, request, done):
        logger.info('RPC getClusterReport [REQ] ' + str(request))
      
        node_state = request.state 

        result = self.cluster.getReport()

        response = yarnproto.GetClusterReportResponseProto()
        for item in result:
            node_report = response.report.nodes.add()
            node_report.hostname = item[0]
            node_report.state = item[1]
            node_report.rack = item[2]
            node_report.container_num = item[3]
            node_report.memory = item[4]
            node_report.cpu = item[5]
            node_report.healthReport = item[6]
            node_report.lastHealthReportTime = item[7]

        logger.info('RPC getClusterReport [RES] ' + str(response))

        done.run(response)

    def getClusterResource(self, controller, request, done):
        logger.info('RPC getClusterResource [REQ] ' + str(request))
      
        node_state = request.state 

        result = self.cluster.getResourceInfo()

        response = yarnproto.GetClusterResourceResponseProto()
        for item in result:
            node_resource = response.resources.nodes.add()
            node_resource.hostname = item[0]
            node_resource.ip = item[1]
            node_resource.min_memory = item[2]
            node_resource.max_memory = item[3]
            node_resource.free_memory = item[4]
            node_resource.min_cpu = item[5]
            node_resource.max_cpu = item[6]
            node_resource.free_cpu = item[7]

        logger.info('RPC getClusterResource [RES] ' + str(response))

        done.run(response)

    def initInvalidResourceResponse(self, response, request_resource_group):
        response.resourceGroup.groupId = 'None'
        resource_id = 0
        for resource in request_resource_group.resources:
            resource_response = response.resourceGroup.resources.add()
            resource_response.id = '%d' % resource_id
            resource_response.hostname = resource.hostname
            resource_response.memory = resource.memory
            resource_response.cpu = resource.cpu
            resource_response.status = -1
            resource_id += 1
