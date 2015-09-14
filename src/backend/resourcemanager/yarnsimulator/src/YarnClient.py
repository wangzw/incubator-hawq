import sys
import traceback
import struct
import socket
import proto.yarnsimulator_pb2 as yarnproto
from protobuf.socketrpc import RpcService

import logging
log = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG)

hostname = 'localhost'
port = 18080


def makeResourceGroup(resource_group, num):
    for i in range(0, num):
        resource = resource_group.add()
        resource.id = '%s' % i
        resource.hostname = 'sdw%d' % (i)
        resource.memory = 1000 * (i + 1)
        resource.cpu = i + 1
        resource.status = 0

create_job_request = yarnproto.CreateJobRequestProto()
create_job_request.jobContext.jobId = 'test_job_id'
create_job_request.jobContext.jobName = 'test_job_name'
create_job_request.jobContext.queue = 'test_queue'
create_job_request.jobContext.status = 'None'

allocate_resource_request = yarnproto.AllocateResourcesRequestProto()
allocate_resource_request.jobId = 'test_job_id'
allocate_resource_request.resourceGroup.groupId = 'test_group_id'
makeResourceGroup(allocate_resource_request.resourceGroup.resources, 3)

active_resource_request = yarnproto.ActiveResourcesRequestProto()
active_resource_request.jobId = 'test_job_id'
active_resource_request.resourceGroup.groupId = 'test_group_id'
makeResourceGroup(active_resource_request.resourceGroup.resources, 3)

release_resource_request = yarnproto.ReleaseResourcesRequestProto()
release_resource_request.jobId = 'test_job_id'
release_resource_request.resourceGroup.groupId = 'test_group_id'
makeResourceGroup(release_resource_request.resourceGroup.resources, 3)

finish_job_request = yarnproto.FinishJobRequestProto()
finish_job_request.jobContext.jobId = 'test_job_id'
finish_job_request.jobContext.jobName = 'test_job_name'
finish_job_request.jobContext.queue = 'test_queue'
finish_job_request.jobContext.status = 'None'

get_clusterreport_request = yarnproto.GetClusterReportRequestProto()
get_clusterreport_request.state = yarnproto.NEW

service = RpcService(yarnproto.YarnSimulatorService_Stub,
                     port,
                     hostname)

#def callback(request, response):
#    log.info('Asynchronous response :' + response.__str__())
#
#try:
#    log.info('Making asynchronous call')
#    response = service.allocateResources(request, callback=callback)
#except Exception, ex:
#    log.exception(ex)
#

"""
try:
    log.info('CreateJob REQ : %s' % (create_job_request))
    response = service.createJob(create_job_request, timeout=10000)
    if not response:
        log.info('CreateJob failed')
    else:
        log.info('CreateJob RES : %s' % (response))
   
    log.info('AllocateResource REQ : %s' % (allocate_resource_request))
    response = service.allocateResources(allocate_resource_request, timeout=10000)
    log.info('AllocateResource RES : %s' % (response))

    log.info('ActiveResource REQ : %s' % (active_resource_request))
    response = service.activeResources(active_resource_request, timeout=10000)
    log.info('ActiveResource RES : %s' % (response))
    
    log.info('ReleaseResource REQ : %s' % (release_resource_request))
    response = service.releaseResources(release_resource_request, timeout=10000)
    log.info('ReleaseResource RES : %s' % (response))
    
    log.info('FinishJob REQ : %s' % (finish_job_request))
    response = service.finishJob(finish_job_request, timeout=10000)
    log.info('FinishJob RES : %s' % (response))

    log.info('GetClusterReport REQ : %s' % (get_clusterreport_request))
    response = service.getClusterReport(get_clusterreport_request, timeout=10000)
    log.info('GetClusterReport RES : %s' % (response))


except Exception as ex:
    log.exception(str(ex))
"""

class Command:
    def __init__(self, param):
        self.param = param
        self.type = ''
        self.request = None
        self.response = None
        self.timeout = 1000

    def parse(self):
        return True

    def execute(self):
        return True

class ClientCommand(Command):
    def __init__(self, param):
        Command.__init__(self, param)
        self.req_header = None
        self.req_content = None
        self.req_tail = struct.pack('<8s', 'MSGENDS!')
        self.res_header = None
        self.res_content = None
        self.res_tail = None
        self.client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

    def parse(self):
        # client register user
        # client allocate connid scansizemb 
        # client release connid
        # client unregister connid
        items = [item.strip() for item in self.param.split(' ') if item.strip() != '']
        if len(items) < 3:
            return False

        self.type = items[1]
        
        if self.type == 'register':
            if len(items) != 3:
                return False
            user = items[2]
            user_length = len(user)
            if (user_length + 4 ) % 8 != 0:
                user_length = user_length + 8 - (user_length + 4) % 8
            content_struct_format = '<I%ds' % (user_length)
            self.req_content = struct.pack(content_struct_format, len(user), user)
            self.req_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 257, len(self.req_content))
        
        elif self.type == 'allocate':
            if len(items) != 4:
                return False
            conn_id = int(items[2])
            scansize = int(items[3])
            self.req_content = struct.pack('<IIII', conn_id, scansize, 0, 0)
            self.req_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 259, len(self.req_content))

        elif self.type == 'release':
            if len(items) != 3:
                return False
            conn_id = int(items[2])
            self.req_content = struct.pack('<II', conn_id, 0)
            self.req_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 260, len(self.req_content))

        elif self.type == 'unregister':
            if len(items) != 3:
                return False
            conn_id = int(items[2])
            self.req_content = struct.pack('<II', conn_id, 0)
            self.req_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 258, len(self.req_content))
        
        else:
            return False
        return True


    def execute(self):
        self.client.connect('/tmp/.s.PGSQL.5436')
        self.client.send(self.req_header)
        self.client.send(self.req_content)
        self.client.send(self.req_tail)
        self.res_header = self.client.recv(16)
        self.res_header = struct.unpack('<8sBBHI', self.res_header)
        (message_begin, id1, id2, message_id, content_length) = self.res_header
        self.res_content = self.client.recv(content_length)
        self.res_tail = self.client.recv(8)

        if self.type == 'register':
            self.response = struct.unpack('<II', self.res_content)
        elif self.type == 'allocate':
            if len(self.res_content) == 8:
                self.response = struct.unpack('<II', self.res_content)
            else:
                resources_length = content_length -4-4-4-4-8
                response_struct_format = '<IIIId%ds' % (resources_length)
                self.response = struct.unpack(response_struct_format, self.res_content)
        elif self.type == 'release':
            self.response = struct.unpack('<II', self.res_content)
        elif self.type == 'unregister':
            self.response = struct.unpack('<II', self.res_content)

        return self.response

class JobCommand(Command):
    def parse(self):
        #job create queue jobname
        #job finish jobid
        items = [item.strip() for item in self.param.split(' ') if item.strip() != '']
        if len(items) <= 2:
            return False

        self.type = items[1]

        if self.type == 'create':
            if len(items) != 4:
                return False
            self.request = yarnproto.CreateJobRequestProto()
            self.request.jobContext.queue = items[2]
            self.request.jobContext.jobName = items[3]
        
        elif self.type == 'finish':
            if len(items) != 3:
                return False
            self.request = yarnproto.FinishJobRequestProto()
            self.request.jobContext.jobId = items[2]
        else:
            return False

        return True

    def execute(self):
        if self.type == 'create':
            self.response = service.createJob(self.request, timeout=self.timeout)
        elif self.type == 'finish': 
            self.response = service.finishJob(self.request, timeout=self.timeout)
        return self.response
        
class ResourceCommand(Command):
    def parse(self):
        #resource allocate jobid groupid (hostname1 memory1 cpu1, hostname2 memory2 cpu2, ...)
        #resource active jobid groupid
        #resource release jobid groupid
        items = [item.strip() for item in self.param.split(' ') if item.strip() != '']
        if len(items) <= 2:
            return False
        
        self.type = items[1]
        
        if self.type == 'allocate':
            items_all = [item.strip() for item in self.param.split('(') if item.strip() != '']
            if len(items_all) != 2:
                return False
            
            items_first = [item.strip() for item in items_all[0].split(' ') if item.strip() != '']
            if len(items_first) != 4:
                return False

            items_second = [item.strip() for item in items_all[1].split(')') if item.strip() != '']
            if len(items_second) != 1:
                return False

            items_res = [item.strip() for item in items_second[0].split(',') if item.strip() != '']
            resources = []
            for item_res in items_res:
                item_data = [item.strip() for item in item_res.split(' ') if item.strip() != '']
                if len(item_data) != 3:
                    return False
                else:
                    resources.append(item_data)

            self.request = yarnproto.AllocateResourcesRequestProto()
            self.request.jobId = items_first[2]
            self.request.resourceGroup.groupId= items_first[3]
            
            for (hostname, memory, cpu) in resources:
                resource = self.request.resourceGroup.resources.add()
                resource.hostname = hostname
                resource.memory = int(memory)
                resource.cpu = int(cpu)

        elif self.type == 'active':
            if len(items) != 4:
                return False
            self.request = yarnproto.ActiveResourcesRequestProto()
            self.request.jobId = items[2] 
            self.request.resourceGroup.groupId = items[3]

        elif self.type == 'release':
            if len(items) != 4:
                return False
            self.request = yarnproto.ReleaseResourcesRequestProto()
            self.request.jobId = items[2] 
            self.request.resourceGroup.groupId = items[3]

        else:
            return False
        
        return True

    def execute(self):
        if self.type == 'allocate':
            self.response = service.allocateResources(self.request, timeout=self.timeout)
        elif self.type == 'active': 
            self.response = service.activeResources(self.request, timeout=self.timeout)
        elif self.type == 'release':
            self.response = service.releaseResources(self.request, timeout=self.timeout)
        return self.response

class ClusterCommand(Command):
    def parse(self):
        # cluster report
        items = [item.strip() for item in self.param.split(' ')  if item.strip() != '']
        if len(items) != 2:
            return False
        
        self.type = items[1]
        if self.type == 'report':
            self.request = yarnproto.GetClusterReportRequestProto()
        elif self.type == 'resource':
            self.request = yarnproto.GetClusterResourceRequestProto()
        else:
            return False
        
        self.request.state = yarnproto.NEW
        return True

    def execute(self):
        if self.type == 'report':
            self.response = service.getClusterReport(self.request, timeout=self.timeout)
        elif self.type == 'resource':
            self.response = service.getClusterResource(self.request, timeout=self.timeout)
        return self.response

class NodeCommand(Command):
    def parse(self):
        print 'node parse', self.param

    def execute(self):
        return 'node execute ' + self.param

def console_welcome():
    print """
  
    ------------------------------------------
    |    WELCOM TO YARN SIMULATOR CLIENT     |
    ------------------------------------------
      
                      _._
                 _.-``   ''-._
            _.-``             ''-._           
        .-``           Yarn       ''-._
       (             Simulator          )     
       |`-._          Client        _.-'|     
       |    `-._       1.0      _.-'    |     
        `-._    `-._        _.-'    _.-'
       |`-._`-._    `-._Y_.-'    _.-'_.'|
       |    `-._`-._        _.-'_.-'    |     
        `-._    `-._`-._A_.-'_.-'    _.-'
       |`-._`-._    `-.___.-'    _.-'_.'|
       |    `-._`-._        _.-'_.-'    |
        `-._    `-._`-._R_.-'_.-'    _.-'
            `-._    `-.___.-'    _.-'
                `-._        _.-'
                    `-._N_.-'
            
     
    """

def console_init():
    print '\rYarnClient>>>',

def console_print(data):
    print '\r', data

def console_quit():
    sys.exit(0) 

def console_input():
    line = sys.stdin.readline()
    line = line.strip('\n')
    line = line.strip() 
    return line

def console_help():
    print """
        YarnClient usage
        help        ->  print help information
        quit        ->  quit YarnClient
        job         ->  create queue jobname 
        job         ->  finish jobid
        resource    ->  allocate jobid groupid (hostname1 memory1 cpu1, hostname2 memory2 cpu2, ...)
        resource    ->  active jobid groupid
        resource    ->  release jobid groupid
        cluster     ->  report
        cluster     ->  resource 
        node        ->  add hostname
        node        ->  remove hostname
        node        ->  get hostname
        client      ->  register user
        client      ->  allocate connid scansizemb
        client      ->  release connid
        client      ->  unregister connid
    """

def gen_command(data):
    items = [item.strip() for item in data.split(' ')]
    if len(items) < 2:
        return None
    command_type = items[0]
    command = None
    if command_type == 'job':
        command = JobCommand(data)
    elif command_type == 'resource':
        command = ResourceCommand(data)
    elif command_type == 'cluster':
        command = ClusterCommand(data)
    elif command_type == 'node':
        command = NodeCommand(data)
    elif command_type == 'client':
        command = ClientCommand(data)
    else:
        return None
    return command

if __name__ == '__main__':
    console_welcome()
    while True: 
        console_init()
        line = console_input()
        
        if not line:
            continue
        elif line == 'help':
            console_help()
        elif line == 'quit':
            console_quit()
        else:
            command = gen_command(line)
            if not command:
                console_print('WRONG COMMAND: %s, TYPE help to get YarnClient usage' % line)
            else:
                if not command.parse():
                    console_print('COMMAND PARAM ERROR: %s, TYPE help to get YarnClient usage' % line)
                else:
                    result = command.execute()
                    console_print(str(result))

