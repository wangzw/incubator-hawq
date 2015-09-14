WORKDIR=.
SRC_DIR=$(WORKDIR)
INC_DIR=$(WORKDIR)

#PROTOBUF=/home/gpadmin/tools/protobuf
PROTOBUF=/usr/local/
#PROTOBUF=/Users/ivan/workplace/tools/protobuf
PROTOBUF_INC=$(PROTOBUF)/include
PROTOBUF_LIB=$(PROTOBUF)/lib

CC=g++
CXXFLAGS=-g -Wall 

INCS=-I$(PROTOBUF_INC) \
	 -I$(INC_DIR)

LIBS=-L$(PROTOBUF_LIB) -lprotobuf \
	 -L$(SRC_DIR) \
	 -lpthread

COMMON_SRCS=rpc.pb.cc yarnsimulator.pb.cc yarnsimulator_client.cpp 

#LIB_TARGET=libyarn.dylib
LIB_TARGET=libyarn.so
TEST_TARGET=libyarn_test

all:
	$(CC) $(CXXFLAGS) -shared -rdynamic -fPIC -o $(LIB_TARGET) $(INCS) $(LIBS) $(COMMON_SRCS) libyarn_protocol.cpp 

test:
	$(CC) $(CXXFLAGS) -o $(TEST_TARGET) libyarn_test.cpp $(INCS) $(LIBS) -lyarn

clean:
	rm $(LIB_TARGET) $(TEST_TARGET)
