/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_ZKFCProtocol_2eproto__INCLUDED
#define PROTOBUF_C_ZKFCProtocol_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Hadoop__Common__CedeActiveRequestProto Hadoop__Common__CedeActiveRequestProto;
typedef struct _Hadoop__Common__CedeActiveResponseProto Hadoop__Common__CedeActiveResponseProto;
typedef struct _Hadoop__Common__GracefulFailoverRequestProto Hadoop__Common__GracefulFailoverRequestProto;
typedef struct _Hadoop__Common__GracefulFailoverResponseProto Hadoop__Common__GracefulFailoverResponseProto;


/* --- enums --- */


/* --- messages --- */

struct  _Hadoop__Common__CedeActiveRequestProto
{
  ProtobufCMessage base;
  uint32_t millistocede;
};
#define HADOOP__COMMON__CEDE_ACTIVE_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__cede_active_request_proto__descriptor) \
    , 0 }


struct  _Hadoop__Common__CedeActiveResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__CEDE_ACTIVE_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__cede_active_response_proto__descriptor) \
     }


struct  _Hadoop__Common__GracefulFailoverRequestProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__GRACEFUL_FAILOVER_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__graceful_failover_request_proto__descriptor) \
     }


struct  _Hadoop__Common__GracefulFailoverResponseProto
{
  ProtobufCMessage base;
};
#define HADOOP__COMMON__GRACEFUL_FAILOVER_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__common__graceful_failover_response_proto__descriptor) \
     }


/* Hadoop__Common__CedeActiveRequestProto methods */
void   hadoop__common__cede_active_request_proto__init
                     (Hadoop__Common__CedeActiveRequestProto         *message);
size_t hadoop__common__cede_active_request_proto__get_packed_size
                     (const Hadoop__Common__CedeActiveRequestProto   *message);
size_t hadoop__common__cede_active_request_proto__pack
                     (const Hadoop__Common__CedeActiveRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__cede_active_request_proto__pack_to_buffer
                     (const Hadoop__Common__CedeActiveRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__CedeActiveRequestProto *
       hadoop__common__cede_active_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__cede_active_request_proto__free_unpacked
                     (Hadoop__Common__CedeActiveRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__CedeActiveResponseProto methods */
void   hadoop__common__cede_active_response_proto__init
                     (Hadoop__Common__CedeActiveResponseProto         *message);
size_t hadoop__common__cede_active_response_proto__get_packed_size
                     (const Hadoop__Common__CedeActiveResponseProto   *message);
size_t hadoop__common__cede_active_response_proto__pack
                     (const Hadoop__Common__CedeActiveResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__cede_active_response_proto__pack_to_buffer
                     (const Hadoop__Common__CedeActiveResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__CedeActiveResponseProto *
       hadoop__common__cede_active_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__cede_active_response_proto__free_unpacked
                     (Hadoop__Common__CedeActiveResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GracefulFailoverRequestProto methods */
void   hadoop__common__graceful_failover_request_proto__init
                     (Hadoop__Common__GracefulFailoverRequestProto         *message);
size_t hadoop__common__graceful_failover_request_proto__get_packed_size
                     (const Hadoop__Common__GracefulFailoverRequestProto   *message);
size_t hadoop__common__graceful_failover_request_proto__pack
                     (const Hadoop__Common__GracefulFailoverRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__common__graceful_failover_request_proto__pack_to_buffer
                     (const Hadoop__Common__GracefulFailoverRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GracefulFailoverRequestProto *
       hadoop__common__graceful_failover_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__graceful_failover_request_proto__free_unpacked
                     (Hadoop__Common__GracefulFailoverRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Common__GracefulFailoverResponseProto methods */
void   hadoop__common__graceful_failover_response_proto__init
                     (Hadoop__Common__GracefulFailoverResponseProto         *message);
size_t hadoop__common__graceful_failover_response_proto__get_packed_size
                     (const Hadoop__Common__GracefulFailoverResponseProto   *message);
size_t hadoop__common__graceful_failover_response_proto__pack
                     (const Hadoop__Common__GracefulFailoverResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__common__graceful_failover_response_proto__pack_to_buffer
                     (const Hadoop__Common__GracefulFailoverResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Common__GracefulFailoverResponseProto *
       hadoop__common__graceful_failover_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__common__graceful_failover_response_proto__free_unpacked
                     (Hadoop__Common__GracefulFailoverResponseProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Common__CedeActiveRequestProto_Closure)
                 (const Hadoop__Common__CedeActiveRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__CedeActiveResponseProto_Closure)
                 (const Hadoop__Common__CedeActiveResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GracefulFailoverRequestProto_Closure)
                 (const Hadoop__Common__GracefulFailoverRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Common__GracefulFailoverResponseProto_Closure)
                 (const Hadoop__Common__GracefulFailoverResponseProto *message,
                  void *closure_data);

/* --- services --- */

typedef struct _Hadoop__Common__ZKFCProtocolService_Service Hadoop__Common__ZKFCProtocolService_Service;
struct _Hadoop__Common__ZKFCProtocolService_Service
{
  ProtobufCService base;
  void (*cede_active)(Hadoop__Common__ZKFCProtocolService_Service *service,
                      const Hadoop__Common__CedeActiveRequestProto *input,
                      Hadoop__Common__CedeActiveResponseProto_Closure closure,
                      void *closure_data);
  void (*graceful_failover)(Hadoop__Common__ZKFCProtocolService_Service *service,
                            const Hadoop__Common__GracefulFailoverRequestProto *input,
                            Hadoop__Common__GracefulFailoverResponseProto_Closure closure,
                            void *closure_data);
};
typedef void (*Hadoop__Common__ZKFCProtocolService_ServiceDestroy)(Hadoop__Common__ZKFCProtocolService_Service *);
void hadoop__common__zkfcprotocol_service__init (Hadoop__Common__ZKFCProtocolService_Service *service,
                                                 Hadoop__Common__ZKFCProtocolService_ServiceDestroy destroy);
#define HADOOP__COMMON__ZKFCPROTOCOL_SERVICE__BASE_INIT \
    { &hadoop__common__zkfcprotocol_service__descriptor, protobuf_c_service_invoke_internal, NULL }
#define HADOOP__COMMON__ZKFCPROTOCOL_SERVICE__INIT(function_prefix__) \
    { HADOOP__COMMON__ZKFCPROTOCOL_SERVICE__BASE_INIT,\
      function_prefix__ ## cede_active,\
      function_prefix__ ## graceful_failover  }
void hadoop__common__zkfcprotocol_service__cede_active(ProtobufCService *service,
                                                       const Hadoop__Common__CedeActiveRequestProto *input,
                                                       Hadoop__Common__CedeActiveResponseProto_Closure closure,
                                                       void *closure_data);
void hadoop__common__zkfcprotocol_service__graceful_failover(ProtobufCService *service,
                                                             const Hadoop__Common__GracefulFailoverRequestProto *input,
                                                             Hadoop__Common__GracefulFailoverResponseProto_Closure closure,
                                                             void *closure_data);

/* --- descriptors --- */

extern const ProtobufCMessageDescriptor hadoop__common__cede_active_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__cede_active_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__graceful_failover_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__common__graceful_failover_response_proto__descriptor;
extern const ProtobufCServiceDescriptor hadoop__common__zkfcprotocol_service__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_ZKFCProtocol_2eproto__INCLUDED */