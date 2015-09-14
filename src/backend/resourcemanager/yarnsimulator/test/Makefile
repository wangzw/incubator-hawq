PROTOBUF=/home/gpadmin/tools/protobuf
PROTOBUF_INC=$(PROTOBUF)/include
PROTOBUF_LIB=$(PROTOBUF)/lib

all:
	g++ -g -o test -I$(PROTOBUF_INC) -L$(PROTOBUF_LIB) test.cpp rpc.pb.cc yarnsimulator.pb.cc libyarn_protocol.cpp -lprotobuf


