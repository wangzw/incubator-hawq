import sys
import os
import time
import logging
import random

logger = logging.getLogger('YarnSimulator')

class Node:
    def __init__(self, hostname, ip):
        self.hostname = hostname
        self.ip = ip
        self.min_memory = 0
        self.max_memory = 0
        self.min_cpu = 0
        self.max_cpu = 0
        self.free_memory = 0
        self.free_cpu = 0
        self.state = 'None'
        self.rack = 'None'
        self.container_num = 0
        self.healthReport = 'None'
        self.lastHealthReport = 0 

    def initResource(self, min_memory=0, max_memory=0, min_cpu=0, max_cpu=0):
        self.min_memory = min_memory 
        self.max_memory = max_memory 
        self.free_memory = max_memory - self.min_memory
        self.min_cpu = min_cpu 
        self.max_cpu = max_cpu 
        self.free_cpu = max_cpu - self.min_cpu

    def allocateResource(self, memory, cpu):
        if self.free_memory >= memory and self.free_cpu >= cpu:
            self.free_memory -= memory
            self.free_cpu -= cpu
            logger.info('Node allocateResource successfully [hostname:%s memory:%d cpu:%d free_memory:%d free_cpu:%d]' \
                    % (self.hostname, memory, cpu, self.free_memory, self.free_cpu))
            return True
        else:
            logger.warn('Node allocateResource not have enough resource [hostname:%s memory:%d cpu:%d free_memory:%d free_cpu:%d]' \
                    % (self.hostname, memory, cpu, self.free_memory, self.free_cpu))
            return False

    def releaseResource(self, memory, cpu):
        allocated_memory = self.max_memory - self.free_memory
        allocated_cpu = self.max_cpu - self.free_cpu
        if allocated_memory >= memory and allocated_cpu >= cpu:
            self.free_memory += memory
            self.free_cpu += cpu
            logger.info('Node releaseResource successfully [hostname:%s memory:%d cpu:%d free_memory:%d free_cpu:%d]' \
                    % (self.hostname, memory, cpu, self.free_memory, self.free_cpu))
            return True
        else:
            logger.warn('Node releaseResource failed. release resource is larger than allocated resource [hostname:%s memory:%d cpu:%d free_memory:%d free_cpu:%d]' \
                    % (self.hostname, memory, cpu, self.free_memory, self.free_cpu))
            return False

    def getReport(self):
        return (self.hostname, self.state, self.rack, self.container_num, \
                self.free_memory, self.free_cpu, self.healthReport, self.lastHealthReport)

    def getResourceInfo(self):
        return (self.hostname, self.ip, self.min_memory, self.max_memory, self.free_memory, \
                self.min_cpu, self.max_cpu, self.free_cpu)

    def dumpNodeInfo(self):
        logger.debug('[NODE] hostname:%s ip:%s memory:[%d,%d,%d] cpu:[%d,%d,%d]' % (self.hostname, self.ip, \
                self.min_memory, self.max_memory, self.free_memory, \
                self.min_cpu, self.max_cpu, self.free_cpu))

class Cluster:
    def __init__(self):
        self.node_list = []
        self.resource_info = {}
        self.memory_block = 0
        self.allocated_memory = 0
        self.allocated_cpu = 0
        self.node_num = 0

    def initClusterInfo(self, cluster_config):
        self.memory_block = int(cluster_config['memory_block'])
        self.resource_info = cluster_config['resource_type']
        self.resource_policy = cluster_config['resource_policy']
        node_list = cluster_config['nodes']
        for node in node_list:
            self.addNode(node['hostname'], node['ip'], \
                    node['min_memory'], node['max_memory'], node['min_cpu'], node['max_cpu'])
        self.node_num = len(self.node_list) 

    def addNode(self, hostname, ip, min_memory, max_memory, min_cpu, max_cpu):
        node = Node(hostname, ip)
        node.initResource(min_memory=min_memory, max_memory=max_memory, min_cpu=min_cpu, max_cpu=max_cpu)
        self.node_list.append(node)

    def removeNode(self, hostname):
        nodeinfo = self.findNodeByHost(hostname)
        if not nodeinfo:
            return False
        else:
            node_idx = nodeinfo[0]
            del self.node_list[node_idx]
            return True

    def findNodeByHost(self, hostname):
        for (node_idx, node) in enumerate(self.node_list):
            if node.hostname == hostname:
                return (node_idx, node)
        return None

    def findNodeByResource(self, hostname, memory, cpu):
        begin_idx = random.randint(0, self.node_num-1)
        node = None
        if hostname and hostname != 'None':
            ret = self.findNodeByHost(hostname)
            if not ret:
                return None
            else:
                begin_idx, node = ret

        for i in range(0, self.node_num):
            node = self.node_list[begin_idx]
            if node.free_memory >= memory and node.free_cpu >= cpu:
                return node
            begin_idx = (begin_idx + 1) % self.node_num
        return None

    def findNodeByPolicy(self, hostname, memory, cpu):
        # TODO find node based on resource policy

        node = self.findNodeByResource(hostname, memory, cpu)
        if not node:
            logger.warn('Cluster findNodeByPolicy failed. [policy:%s hostname:%s memory:%d cpu=%d]' \
                    % (self.resource_policy, hostname, memory, cpu))
        else:
            logger.debug('Cluster findNodeByPolicy. [policy:%s hostname:%s memory:%d cpu=%d node:%s]' \
                    % (self.resource_policy, hostname, memory, cpu, node.hostname))
        return node

    def allocateNodeResource(self, hostname, memory, cpu):
        real_memory = memory
        if real_memory % self.memory_block != 0:
            real_memory = (real_memory / self.memory_block + 1) * self.memory_block

        node = self.findNodeByPolicy(hostname, real_memory, cpu)
        if not node:
            logger.warn('Cluster allocateNodeResource failed. [hostname:%s memory:%d cpu:%d]' % (hostname, memory, cpu))
            return None
        else:
            if not node.allocateResource(real_memory, cpu):
                logger.warn('Cluster node allocateNodeResource failed. [node:%s hostname:%s memory:%d cpu:%d]' \
                        % (node.hostname, hostname, memory, cpu))
                return None
            else:
                self.allocated_memory += real_memory
                self.allocated_cpu += cpu
            logger.info('Cluster allocateNodeResource successfully. [node:%s hostname:%s memory:%d cpu:%d]' \
                    % (node.hostname, hostname, memory, cpu))
            return (node.hostname, real_memory, cpu, 0)

    def releaseNodeResource(self, hostname, memory, cpu):
        ret = self.findNodeByHost(hostname)
        if not ret:
            logger.warn('Cluster releaseNodeResource failed. [hostname:%s memory:%d cpu:%d]' % (hostname, memory, cpu))
            return False
        else:
            node_idx, node = ret
            if not node.releaseResource(memory, cpu):
                logger.warn('Cluster node releaseNodeResource failed. [node:%s hostname:%s memory:%d cpu:%d]' \
                        % (node.hostname, hostname, memory, cpu))
                return False
            else:
                self.allocated_memory -= memory
                self.allocated_cpu -= cpu
            logger.info('Cluster releaseNodeResource successfully. [node:%s hostname:%s memory:%d cpu:%d]' \
                    % (node.hostname, hostname, memory, cpu))
            return True

    def allocateResource(self, resource_group):
        resource_result = []

        for (ridx, resource) in enumerate(resource_group):
            hostname, memory, cpu = resource
            result = self.allocateNodeResource(hostname, memory, cpu)
            if not result:
                logger.warn('Cluster allocateResource failed. [hostname:%s memory:%d cpu:%d]' % (hostname, memory, cpu))
                continue 
            else:
                hostname_result, memory_result, cpu_result, status_result = result
                resource_result.append((str(ridx), hostname_result, memory_result, cpu_result, status_result))
        
        if not resource_result:        
            logger.warn('Cluster allocateResource failed. [resource_group:%s]' % str(resource_group))
        else:
            logger.info('Cluster allocateResource successfully. [resource_group:%s result:%s]' \
                % (str(resource_group), str(resource_result)))
        return resource_result

    def activeResource(self, resource_group):
        resource_result = []
        
        # TODO no implement for active
        resource_result = resource_group

        logger.info('Cluster activeResource successfully. [resource_group:%s result:%s]' \
                % (str(resource_group), str(resource_result)))
        return resource_result

    def releaseResource(self, resource_group):
        resource_result = []

        for (id, hostname, memory, cpu, status) in resource_group:
            result = self.releaseNodeResource(hostname, memory, cpu)
            if not result:
                logger.warn('Cluster releaseResource failed. [hostname:%s memory:%d cpu:%d]' % (hostname, memory, cpu))
                continue
            else:
                resource_result.append((id, hostname, memory, cpu, status))
 
        logger.info('Cluster releaseResource successfully. [resource_group:%s result:%s]' \
                % (str(resource_group), str(resource_result)))
        
        return resource_result

    def getReport(self):
        report = []
        for node in self.node_list:
            report.append(node.getReport())
        return report

    def getResourceInfo(self):
        result = []
        for node in self.node_list:
            result.append(node.getResourceInfo())
        return result 

    def dumpClusterInfo(self):
        for node in self.node_list:
            node.dumpNodeInfo()

