import os
import sys
import logging
import optparse
import threading

import Config
import Cluster
import ResourceTrack

import proto.yarnsimulator_pb2
import protobuf.socketrpc.server as rpcserver
import server.RpcServer as rpcservice
import server.HttpServer as httpservice

logger = logging.getLogger('YarnSimulator')
config = Config.Config()

def optParse():
    parser = optparse.OptionParser()
    parser.add_option('-c', '--config', dest='config_file', help='YarnSimulator configuration file')
    (options, args) = parser.parse_args()
    if not options.config_file:
        parser.print_help()
        raise Exception('invalid options')
    return options

def initLog():
    log_formatter = logging.Formatter('[%(asctime)s] [%(levelname)-8s] %(message)s', '%Y %H:%M:%S',)
    log_file = config.get('global', 'log_dir') + os.sep + config.get('global', 'log_file')
    log_handler = logging.FileHandler(log_file)
    log_handler.setFormatter(log_formatter)
    logger.addHandler(log_handler)
    log_level = config.get('global', 'log_level')
    if log_level == 'fatal':
        logger.setLevel(logging.FATAL)
    elif log_level == 'error':
        logger.setLevel(logging.ERROR)
    elif log_level == 'warn':
        logger.setLevel(logging.WARN)
    elif log_level == 'info':
        logger.setLevel(logging.INFO)
    else:
        logger.setLevel(logging.DEBUG)

def rpc_service_run(port, cluster_info, resource_tracker):
    yarnRpcService = rpcservice.YarnSimulatorService(cluster_info, resource_tracker)
    yarnRpcServer = rpcserver.SocketRpcServer(port)
    yarnRpcServer.registerService(yarnRpcService)
    logger.info('yarn simulator rpc service run on port %d' % port)
    yarnRpcServer.run()

def http_service_run(port, cluster_info, resource_tracker):
    httpService = httpservice.HttpService(port, cluster_info, resource_tracker)
    logger.info('yarn simulator http service run on port %d' % port)
    httpService.run()

def main():
    try:
        options = optParse()
        config.loadConf(options.config_file)
        initLog()

        cluster = Cluster.Cluster()
        cluster.initClusterInfo(config.getClusterConfig())
        
        resource_tracker = ResourceTrack.ResourceTrack(config.getResourceQueue())

        logger.debug(config.getClusterConfig())
        
        # start yarn simulator services
        rpc_port = config.getint('service', 'rpc_port')
        rpc_service_thread = threading.Thread(target=rpc_service_run,args=(rpc_port, cluster, resource_tracker))
        rpc_service_thread.setDaemon(True)
        rpc_service_thread.start()

        # start http service
        http_port = config.getint('service', 'http_port')
        http_service_thread = threading.Thread(target=http_service_run,args=(http_port, cluster, resource_tracker))
        http_service_thread.setDaemon(True)
        http_service_thread.start()
        
        rpc_service_thread.join()
        http_service_thread.join()

    except Exception, e:
        print e
        return 1

    return 0


if __name__ == '__main__':
    sys.exit(main())
