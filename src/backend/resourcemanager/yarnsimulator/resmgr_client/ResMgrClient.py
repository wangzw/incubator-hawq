import socket, time
import struct

user_id = 'gpadmin'
content = struct.pack('<I12s', len(user_id), user_id)
print content, len(content)

header = struct.pack('<8sBBHI', 'MSGSTART', 0x80, 0, 257, len(content))
print header, len(header)
tail = struct.pack('<8s', 'MSGENDS!')

#client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#client.connect(('localhost', 5436))
client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
client.connect('/tmp/.s.PGSQL.5436')
client.send(header)
client.send(content)
client.send(tail)


recv_header = client.recv(16)
unpack_header =  struct.unpack('<8sBBHI', recv_header)
print unpack_header
(message_begin, id1, id2, message_id, content_length) = unpack_header
recv_content = client.recv(content_length)
unpack_content = struct.unpack('<II', recv_content)
print unpack_content
recv_tail = client.recv(8)
print recv_tail

time.sleep(1)
