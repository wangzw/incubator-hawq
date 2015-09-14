#ifndef _HD_CLIENT_HADOOP_RPC_UTILS_H_
#define _HD_CLIENT_HADOOP_RPC_UTILS_H_

#include <google/protobuf-c/protobuf-c.h>
#include <stdbool.h>
#include <pthread.h>

typedef enum {
  APPLICATION_CLIENT_PROTOCOL = 0,
  APPLICATION_MASTER_PROTOCOL = 1,
  CONTAINER_MANAGEMENT_PROTOCOL = 2,
  LIBYARN_PROTOCOL = 3
} yarn_protocol_type_t;

/**
 * struct define of PB proxy client
 */
typedef struct {
  int caller_id;                     /* caller-id, assume user shouldn't access this */
  int socket_id;                     /* socket-id, assume user shouldn't access this */
  const char* protocol_name;         /* name of protocol, assume user shouldn't access this */
  int app_id;                        /* application-id */
  int app_attempt_id;                /* application-attempt-id */
  int64_t cluster_timestamp;         /* time stamp of the cluster */
  char* uuid;                        /* uuid buffer to RPC client */
  int uuid_len;                      /* length of uuid buffer */
  pthread_mutex_t lock;              /* lock object */
} hadoop_rpc_proxy_t;

// create rpc proxy with specified protocol_name and type, return NULL if failed
hadoop_rpc_proxy_t* create_new_yarn_rpc_proxy(yarn_protocol_type_t t);

hadoop_rpc_proxy_t* create_new_general_rpc_proxy(const char* name);

// setup connection for this proxy with specified host and port, return 0 if succeed
int setup_connection(const hadoop_rpc_proxy_t* proxy, const char* host, int port);

// utils func which will be internally used by protocols
char* generate_delimited_message(const ProtobufCMessage *message, int* length_out);

/* send the whole rpc payload to socket, will add header for it */
int send_rpc_request(hadoop_rpc_proxy_t* proxy, 
    const char* method, 
    const char* msg,
    int msg_len);

/* read header of response,
 * it will return actual response message if succeed
 * it will return NULL if failed/error, and print error messages
 */ 
char* recv_rpc_response(hadoop_rpc_proxy_t* proxy, int* response_msg_len);


#endif //_HD_CLIENT_HADOOP_RPC_UTILS_H_
