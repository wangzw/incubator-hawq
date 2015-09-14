import ConfigParser

class Config:
    def __init__(self):
        self.config = ConfigParser.ConfigParser()
        self.cluster = {}

    def loadConf(self, config_file):
        self.config.read(config_file)

    def get(self, section, field):
        return self.config.get(section, field)

    def getint(self, section, field):
        return self.config.getint(section, field)

    def splitRange(self, range):
        # range format : [min-max]
        min, max = range.split('[')[1].split(']')[0].split('-')
        return (int(min), int(max))

    def getResourceQueue(self):
        return self.cluster['resource_queue']

    def allocateHostnameForCluster(self, node_list, hostname_range):
        hostname_prefix = hostname_range.split('[')[0]
        hostname_id_min, hostname_id_max = self.splitRange(hostname_range)
        for i in range(hostname_id_min, hostname_id_max+1):
            node_info = {}
            node_info['hostname'] = '%s%d' % (hostname_prefix, i) 
            node_list.append(node_info)
    
    def allocateIpForCluster(self, node_list, ip_list):
        for (node_idx, node) in enumerate(node_list):
            node['ip'] = ip_list[node_idx]

    def getIpList(self, ip_range):
        ip_ids = [(0, 0), (0, 0), (0, 0), (0, 0)]
        for (idx, ip_item) in enumerate(ip_range.split('.')):
            if ip_item[0] == '[' and ip_item[-1] == ']':
                ip_min, ip_max = self.splitRange(ip_item)
                ip_ids[idx] = (ip_min, ip_max)
            else:
                ip_ids[idx] = (int(ip_item), int(ip_item))

        ip_list = []
        for i in range(ip_ids[0][0], ip_ids[0][1] + 1):
            for j in range(ip_ids[1][0], ip_ids[1][1] + 1):
                for k in range(ip_ids[2][0], ip_ids[2][1] + 1):
                    for m in range(ip_ids[3][0], ip_ids[3][1] + 1):
                        ip_list.append('%d.%d.%d.%d' % (i, j, k, m))
        return ip_list

    def allocateResourceForHosts(self, node_list, resource_info, hostname_range):
        hostname_prefix = hostname_range.split('[')[0]
        hostname_id_min, hostname_id_max = self.splitRange(hostname_range)
        for i in range(hostname_id_min, hostname_id_max+1):
            hostname = '%s%i' % (hostname_prefix, i)
            for node in node_list:
                if node['hostname'] != hostname:
                    continue

                if not node.has_key('min_memory'):
                    node['min_memory'] = resource_info['min_memory']
                if not node.has_key('max_memory'):
                    node['max_memory'] = resource_info['max_memory']
                if not node.has_key('min_cpu'):
                    node['min_cpu'] = resource_info['min_cpu']
                if not node.has_key('max_cpu'):
                    node['max_cpu'] = resource_info['max_cpu']

    def updateResourceForClusterByDefault(self, node_list, resource_info):
        for node in node_list:
            if not node.has_key('min_memory'):
                node['min_memory'] = resource_info['min_memory']
            if not node.has_key('max_memory'):
                node['max_memory'] = resource_info['max_memory']
            if not node.has_key('min_cpu'):
                node['min_cpu'] = resource_info['min_cpu']
            if not node.has_key('max_cpu'):
                node['max_cpu'] = resource_info['max_cpu']


    def getClusterConfig(self):
        node_source = self.config.get('cluster', 'node_source')
        if node_source == 'simulator':
            self.cluster['node_num'] = self.config.getint('cluster', 'node_num')
            self.cluster['nodes'] = []
            
            # allocate node hostname
            node_hostname_range = self.config.get('cluster', 'hostname_range')
            self.allocateHostnameForCluster(self.cluster['nodes'], node_hostname_range)
            
            # allocate node ip
            node_ip_range = self.config.get('cluster', 'ip_range')
            node_ip_list = self.getIpList(node_ip_range)

            # check node_num, hostname_num, ip_num
            if self.cluster['node_num'] != len(self.cluster['nodes']) \
                or self.cluster['node_num'] > len(node_ip_list):
                raise Exception('cluster node number do not match hostname or ip number')
            
            self.allocateIpForCluster(self.cluster['nodes'], node_ip_list)

            # allocate node resource
            self.cluster['resource_policy'] = self.config.get('cluster', 'resource_policy')
            self.cluster['memory_block'] = self.config.get('cluster', 'memory_block')

            # allocate resouce
            self.cluster['resource_type'] = {}
            for section in self.config.sections():
                if section.find('cluster_resource_') == 0:
                    resource_type = section[len('cluster_resource_'):]
                    memory = self.config.get(section, 'memory')
                    cpu = self.config.get(section, 'cpu')
                    min_memory, max_memory = [int(memory.strip()) for memory in memory.split(',')]
                    min_cpu, max_cpu = [int(cpu.strip()) for cpu in cpu.split(',')]
                    resource_info = {}
                    resource_info['min_memory'] = min_memory
                    resource_info['max_memory'] = max_memory
                    resource_info['min_cpu'] = min_cpu
                    resource_info['max_cpu'] = max_cpu
                    self.cluster['resource_type'][resource_type] = resource_info
                    
                    if resource_type != 'default':
                        hostname_range = self.config.get(section, 'hosts') 
                        self.allocateResourceForHosts(self.cluster['nodes'], resource_info, hostname_range)

            self.updateResourceForClusterByDefault(self.cluster['nodes'], self.cluster['resource_type']['default'])

            # load queue info
            queues = self.config.get('cluster', 'resource_queue')
            self.cluster['resource_queue'] = [queue.strip() for queue in queues.split(',')] 

        elif node_source == 'hawq':
            # TODO get cluster node info from hawq db
            raise Exception('hawq node source have not implementated')
        else:
            raise Exception('invalid node source')

        return self.cluster

if __name__ == '__main__':
    config = Config()
    import sys
    config.loadConf(sys.argv[1])
    config.getClusterConfig()

