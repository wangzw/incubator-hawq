import sys
import os
import logging

logger = logging.getLogger('YarnSimulator')

class ResourceTrack:
    def __init__(self, resource_queue):
        #track_info : queue -> job -> group -> resources
        self.track_info = {}
        
        for queue in resource_queue:
            self.track_info[queue] = {} 

        # job_id -> (queue, job_name)
        self.jobs = {} 
        
        self.job_id = 0
        self.group_id = 0

    def genGlobalJobId(self):
        self.job_id += 1
        return 'yarn_simulator_auto_jobid_%d' % (self.job_id)

    def existJob(self, job_id):
        return self.jobs.has_key(job_id)

    def existQueue(self, queue):
        return self.track_info.has_key(queue)

    def existResourceGroup(self, job_id, group_id, resources = None):
        # check job id
        if not self.existJob(job_id):
            return False
        else:
            queue, job_name = self.jobs[job_id]
            # check group id
            if not self.track_info[queue][job_id].has_key(group_id):
                return False
            else:
                # check resource group
                if resources and resources != self.track_info[queue][job_id][group_id]:
                    return False
        return True

    def getResourceGroup(self, job_id, group_id):
        if not self.existResourceGroup(job_id, group_id):
            return None
        else:
            queue, job_name = self.jobs[job_id]
            return self.track_info[queue][job_id][group_id]

    def getJobInfo(self, job_id):
        if not self.existJob(job_id):
            logger.warn('ResourceTrack getJobInfo failed. job id not exist. [jobid:%s]' % job_id)
            return None
        else:
            queue, jobname = self.jobs[job_id]
            return (queue, jobname)

    def addJobInfo(self, queue, job_id, job_name):
        if not self.existQueue(queue):
            logger.warn('ResourceTrack addJobInfo failed. queue not exist. [queue:%s jobid:%s jobname:%s]' \
                    % (queue, job_id, job_name))
            return False

        if self.existJob(job_id):
            logger.warn('ResourceTrack addJobInfo failed. job id exist. [queue:%s jobid:%s jobname:%s]' \
                    % (queue, job_id, job_name))
            return False
        
        self.track_info[queue][job_id] = {}
        self.jobs[job_id] = (queue, job_name)
        return True

    def removeJobInfo(self, job_id):
        if not self.existJob(job_id):
            logger.warn('ResourceTrack removeJobInfo failed. job id not exist. [jobid:%s]' % job_id)
            return False
        
        queue, jobname = self.getJobInfo(job_id)
        del self.track_info[queue][job_id]
        del self.jobs[job_id]
        
        return True

    def addResourceInfo(self, job_id, group_id, resources):
        if not self.existJob(job_id):
            logger.warn('ResourceTrack addResourceInfo failed. job id not exist. [jobid:%s]' \
                    % (job_id))
            return False
        
        if self.existResourceGroup(job_id, group_id):
            logger.warn('ResourceTrack addResourceInfo failed. resource group exist. [jobid:%s groupid:%s]' \
                    % (job_id, group_id))
            return False

        queue, jobname = self.jobs[job_id]
        self.track_info[queue][job_id][group_id] = resources 
        return True

    def removeResourceInfo(self, job_id, group_id, resources):
        if not self.existJob(job_id):
            logger.warn('ResourceTrack removeResourceInfo failed. job id not exist. [jobid:%s]' \
                    % (job_id))
            return False
        
        if not self.existResourceGroup(job_id, group_id):
            logger.warn('ResourceTrack removeResourceInfo failed. resource group not exist. [jobid:%s groupid:%s]' \
                    % (job_id, group_id))
            return False

        queue, jobname = self.jobs[job_id]
        del self.track_info[queue][job_id][group_id] 
        return True

