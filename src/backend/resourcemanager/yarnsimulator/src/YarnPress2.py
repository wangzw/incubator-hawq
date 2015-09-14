import sys
import traceback
import struct
import socket
import threading
import time
import random
import logging
log = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG)

concurrency = 200
iterator = 5000

client_cost = {}
client_cost['register'] = []
#client_cost['allocate'] = []
client_cost['release'] = []
client_cost['unregister'] = []

def client_process_request(client, request_header, request_content, request_tail):
    client.send(request_header)
    client.send(request_content)
    client.send(request_tail)
    response_header = client.recv(16)
    response_header = struct.unpack('<8sBBHI', response_header)
    (message_begin, id1, id2, message_id, content_length) = response_header
    response_content = client.recv(content_length)
    response_tail = client.recv(8)
    #print 'received content length:',content_length
    return response_content

def client_register(client, user):
    user_length = len(user)
    if (user_length + 4 ) % 8 != 0:
        user_length = user_length + 8 - (user_length + 4) % 8
    content_struct_format = '<I%ds' % (user_length)
    request_content = struct.pack(content_struct_format, len(user), user)
    request_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 257, len(request_content))
    request_tail = struct.pack('<8s', 'MSGENDS!')
    cost = time.time()
    response_content = client_process_request(client, request_header, request_content, request_tail)
    cost = time.time() - cost
    cost = int(cost * 1000000)
    client_cost['register'].append(cost)
    log.info('client register : %dus' % cost)
    return struct.unpack('<II', response_content)

def client_allocate(client, conn_id, scansizemb):
    request_content = struct.pack('<IIII', conn_id, scansizemb, 0, 0)
    request_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 259, len(request_content))
    request_tail = struct.pack('<8s', 'MSGENDS!')
    #cost = time.time()
    response_content = client_process_request(client, request_header, request_content, request_tail)
    #cost = time.time() - cost
    #cost = int(cost * 1000000)
    #client_cost['allocate'].append(cost)
    #log.info('client allocate : %dus' % cost)
    if len(response_content) == 8:
        return struct.unpack('<II', response_content)
    else:
        resources_length = len(response_content) -4-4-4-4-8
        response_struct_format = '<IIIId%ds' % (resources_length)
        return struct.unpack(response_struct_format, response_content)

def client_release(client, conn_id):
	request_content = struct.pack('<II', conn_id, 0)
	request_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 260, len(request_content))
	request_tail = struct.pack('<8s', 'MSGENDS!')
    #cost = time.time()
	response_content = client_process_request(client, request_header, request_content, request_tail)
    #cost = time.time() - cost
    #cost = int(cost * 1000000)
    #client_cost['release'].append(cost)
    #log.info('client release : %dus' % cost)
	return struct.unpack('<II', response_content)

def client_unregister(client, conn_id):
    request_content = struct.pack('<II', conn_id, 0)
    request_header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 258, len(request_content))
    request_tail = struct.pack('<8s', 'MSGENDS!')
    cost = time.time()
    response_content = client_process_request(client, request_header, request_content, request_tail)
    cost = time.time() - cost
    cost = int(cost * 1000000)
    client_cost['unregister'].append(cost)
    log.info('client unregister : %dus' % cost)
    return struct.unpack('<II', response_content)

def client_wait(seconds):
    time.sleep(seconds)

def worker(worker_id):

	client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
	client.connect('/tmp/.s.PGSQL.5436')
	(conn_id, status) =  client_register(client, 'gpadmin')

	cost = time.time()
    #cost = time.time() - cost
    #cost = int(cost * 1000000)
    #client_cost['release'].append(cost)
    #log.info('client release : %dus' % cost)

	for i in range(iterator):
		client_allocate(client, conn_id, 102400)
		client_release(client, conn_id)

	cost = time.time() - cost
	cost = int(cost * 1000000)
	client_cost['release'].append(cost);

	client_unregister(client, conn_id)

if __name__ == '__main__':
    thread_list = []
    for i in range(concurrency):
        t = threading.Thread(target=worker, args=(i,))
        thread_list.append(t)
        t.start()
   
    for t in thread_list:
        t.join()

    for (k, v) in client_cost.items():
        total = sum(v)
        avgvalue = total / len(v)
        maxvalue = max(v)
        print k, 'avg:%d'%avgvalue, 'max:%d'%maxvalue






