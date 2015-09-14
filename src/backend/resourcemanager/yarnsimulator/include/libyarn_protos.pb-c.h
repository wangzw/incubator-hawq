/* Generated by the protocol buffer compiler.  DO NOT EDIT! */

#ifndef PROTOBUF_C_libyarn_5fprotos_2eproto__INCLUDED
#define PROTOBUF_C_libyarn_5fprotos_2eproto__INCLUDED

#include <google/protobuf-c/protobuf-c.h>

PROTOBUF_C_BEGIN_DECLS


typedef struct _Hadoop__Yarn__LibYarnResourceProto Hadoop__Yarn__LibYarnResourceProto;
typedef struct _Hadoop__Yarn__LibYarnAllocateResourceRequestProto Hadoop__Yarn__LibYarnAllocateResourceRequestProto;
typedef struct _Hadoop__Yarn__LibYarnAllocateResourceResponseProto Hadoop__Yarn__LibYarnAllocateResourceResponseProto;
typedef struct _Hadoop__Yarn__LibYarnReleaseResourceRequestProto Hadoop__Yarn__LibYarnReleaseResourceRequestProto;
typedef struct _Hadoop__Yarn__LibYarnReleaseResourceResponseProto Hadoop__Yarn__LibYarnReleaseResourceResponseProto;
typedef struct _Hadoop__Yarn__LibYarnActiveResourceRequestProto Hadoop__Yarn__LibYarnActiveResourceRequestProto;
typedef struct _Hadoop__Yarn__LibYarnActiveResourceResponseProto Hadoop__Yarn__LibYarnActiveResourceResponseProto;
typedef struct _Hadoop__Yarn__LibYarnCreateJobRequestProto Hadoop__Yarn__LibYarnCreateJobRequestProto;
typedef struct _Hadoop__Yarn__LibYarnCreateJobResponseProto Hadoop__Yarn__LibYarnCreateJobResponseProto;
typedef struct _Hadoop__Yarn__LibYarnFinishJobRequestProto Hadoop__Yarn__LibYarnFinishJobRequestProto;
typedef struct _Hadoop__Yarn__LibYarnFinishJobResponseProto Hadoop__Yarn__LibYarnFinishJobResponseProto;
typedef struct _Hadoop__Yarn__SayHiRequestProto Hadoop__Yarn__SayHiRequestProto;
typedef struct _Hadoop__Yarn__SayHiResponseProto Hadoop__Yarn__SayHiResponseProto;


/* --- enums --- */

typedef enum _Hadoop__Yarn__ResourceStatusProto {
  HADOOP__YARN__RESOURCE_STATUS_PROTO__NOT_ACQUIRED = 1,
  HADOOP__YARN__RESOURCE_STATUS_PROTO__IDLE = 2,
  HADOOP__YARN__RESOURCE_STATUS_PROTO__BUSY = 3
} Hadoop__Yarn__ResourceStatusProto;

/* --- messages --- */

struct  _Hadoop__Yarn__LibYarnResourceProto
{
  ProtobufCMessage base;
  char *id;
  char *host;
  char *rack;
  int32_t memory;
  int32_t vcores;
  protobuf_c_boolean has_relax;
  protobuf_c_boolean relax;
  Hadoop__Yarn__ResourceStatusProto status;
};
extern char hadoop__yarn__lib_yarn_resource_proto__id__default_value[];
#define HADOOP__YARN__LIB_YARN_RESOURCE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_resource_proto__descriptor) \
    , hadoop__yarn__lib_yarn_resource_proto__id__default_value, NULL, NULL, 0, 0, 0,1, HADOOP__YARN__RESOURCE_STATUS_PROTO__NOT_ACQUIRED }


struct  _Hadoop__Yarn__LibYarnAllocateResourceRequestProto
{
  ProtobufCMessage base;
  char *jobid;
  char *groupid;
  size_t n_resources;
  Hadoop__Yarn__LibYarnResourceProto **resources;
};
#define HADOOP__YARN__LIB_YARN_ALLOCATE_RESOURCE_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_allocate_resource_request_proto__descriptor) \
    , NULL, NULL, 0,NULL }


struct  _Hadoop__Yarn__LibYarnAllocateResourceResponseProto
{
  ProtobufCMessage base;
  char *groupid;
  size_t n_resources;
  Hadoop__Yarn__LibYarnResourceProto **resources;
};
#define HADOOP__YARN__LIB_YARN_ALLOCATE_RESOURCE_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_allocate_resource_response_proto__descriptor) \
    , NULL, 0,NULL }


struct  _Hadoop__Yarn__LibYarnReleaseResourceRequestProto
{
  ProtobufCMessage base;
  char *jobid;
  char *groupid;
  size_t n_resources;
  Hadoop__Yarn__LibYarnResourceProto **resources;
};
#define HADOOP__YARN__LIB_YARN_RELEASE_RESOURCE_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_release_resource_request_proto__descriptor) \
    , NULL, NULL, 0,NULL }


struct  _Hadoop__Yarn__LibYarnReleaseResourceResponseProto
{
  ProtobufCMessage base;
  char *groupid;
  size_t n_resources;
  Hadoop__Yarn__LibYarnResourceProto **resources;
};
#define HADOOP__YARN__LIB_YARN_RELEASE_RESOURCE_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_release_resource_response_proto__descriptor) \
    , NULL, 0,NULL }


struct  _Hadoop__Yarn__LibYarnActiveResourceRequestProto
{
  ProtobufCMessage base;
  char *jobid;
  char *groupid;
  size_t n_resources;
  Hadoop__Yarn__LibYarnResourceProto **resources;
};
#define HADOOP__YARN__LIB_YARN_ACTIVE_RESOURCE_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_active_resource_request_proto__descriptor) \
    , NULL, NULL, 0,NULL }


struct  _Hadoop__Yarn__LibYarnActiveResourceResponseProto
{
  ProtobufCMessage base;
  char *groupid;
  size_t n_resources;
  Hadoop__Yarn__LibYarnResourceProto **resources;
};
#define HADOOP__YARN__LIB_YARN_ACTIVE_RESOURCE_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_active_resource_response_proto__descriptor) \
    , NULL, 0,NULL }


struct  _Hadoop__Yarn__LibYarnCreateJobRequestProto
{
  ProtobufCMessage base;
  char *jobname;
  char *queue;
};
#define HADOOP__YARN__LIB_YARN_CREATE_JOB_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_create_job_request_proto__descriptor) \
    , NULL, NULL }


struct  _Hadoop__Yarn__LibYarnCreateJobResponseProto
{
  ProtobufCMessage base;
  char *jobid;
};
#define HADOOP__YARN__LIB_YARN_CREATE_JOB_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_create_job_response_proto__descriptor) \
    , NULL }


struct  _Hadoop__Yarn__LibYarnFinishJobRequestProto
{
  ProtobufCMessage base;
  char *jobid;
};
#define HADOOP__YARN__LIB_YARN_FINISH_JOB_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_finish_job_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Yarn__LibYarnFinishJobResponseProto
{
  ProtobufCMessage base;
  char *msg;
};
#define HADOOP__YARN__LIB_YARN_FINISH_JOB_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__lib_yarn_finish_job_response_proto__descriptor) \
    , NULL }


struct  _Hadoop__Yarn__SayHiRequestProto
{
  ProtobufCMessage base;
  char *name;
};
#define HADOOP__YARN__SAY_HI_REQUEST_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__say_hi_request_proto__descriptor) \
    , NULL }


struct  _Hadoop__Yarn__SayHiResponseProto
{
  ProtobufCMessage base;
  char *msg;
};
#define HADOOP__YARN__SAY_HI_RESPONSE_PROTO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&hadoop__yarn__say_hi_response_proto__descriptor) \
    , NULL }


/* Hadoop__Yarn__LibYarnResourceProto methods */
void   hadoop__yarn__lib_yarn_resource_proto__init
                     (Hadoop__Yarn__LibYarnResourceProto         *message);
size_t hadoop__yarn__lib_yarn_resource_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnResourceProto   *message);
size_t hadoop__yarn__lib_yarn_resource_proto__pack
                     (const Hadoop__Yarn__LibYarnResourceProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_resource_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnResourceProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnResourceProto *
       hadoop__yarn__lib_yarn_resource_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_resource_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnResourceProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnAllocateResourceRequestProto methods */
void   hadoop__yarn__lib_yarn_allocate_resource_request_proto__init
                     (Hadoop__Yarn__LibYarnAllocateResourceRequestProto         *message);
size_t hadoop__yarn__lib_yarn_allocate_resource_request_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnAllocateResourceRequestProto   *message);
size_t hadoop__yarn__lib_yarn_allocate_resource_request_proto__pack
                     (const Hadoop__Yarn__LibYarnAllocateResourceRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_allocate_resource_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnAllocateResourceRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnAllocateResourceRequestProto *
       hadoop__yarn__lib_yarn_allocate_resource_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_allocate_resource_request_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnAllocateResourceRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnAllocateResourceResponseProto methods */
void   hadoop__yarn__lib_yarn_allocate_resource_response_proto__init
                     (Hadoop__Yarn__LibYarnAllocateResourceResponseProto         *message);
size_t hadoop__yarn__lib_yarn_allocate_resource_response_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnAllocateResourceResponseProto   *message);
size_t hadoop__yarn__lib_yarn_allocate_resource_response_proto__pack
                     (const Hadoop__Yarn__LibYarnAllocateResourceResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_allocate_resource_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnAllocateResourceResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnAllocateResourceResponseProto *
       hadoop__yarn__lib_yarn_allocate_resource_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_allocate_resource_response_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnAllocateResourceResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnReleaseResourceRequestProto methods */
void   hadoop__yarn__lib_yarn_release_resource_request_proto__init
                     (Hadoop__Yarn__LibYarnReleaseResourceRequestProto         *message);
size_t hadoop__yarn__lib_yarn_release_resource_request_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnReleaseResourceRequestProto   *message);
size_t hadoop__yarn__lib_yarn_release_resource_request_proto__pack
                     (const Hadoop__Yarn__LibYarnReleaseResourceRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_release_resource_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnReleaseResourceRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnReleaseResourceRequestProto *
       hadoop__yarn__lib_yarn_release_resource_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_release_resource_request_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnReleaseResourceRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnReleaseResourceResponseProto methods */
void   hadoop__yarn__lib_yarn_release_resource_response_proto__init
                     (Hadoop__Yarn__LibYarnReleaseResourceResponseProto         *message);
size_t hadoop__yarn__lib_yarn_release_resource_response_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnReleaseResourceResponseProto   *message);
size_t hadoop__yarn__lib_yarn_release_resource_response_proto__pack
                     (const Hadoop__Yarn__LibYarnReleaseResourceResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_release_resource_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnReleaseResourceResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnReleaseResourceResponseProto *
       hadoop__yarn__lib_yarn_release_resource_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_release_resource_response_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnReleaseResourceResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnActiveResourceRequestProto methods */
void   hadoop__yarn__lib_yarn_active_resource_request_proto__init
                     (Hadoop__Yarn__LibYarnActiveResourceRequestProto         *message);
size_t hadoop__yarn__lib_yarn_active_resource_request_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnActiveResourceRequestProto   *message);
size_t hadoop__yarn__lib_yarn_active_resource_request_proto__pack
                     (const Hadoop__Yarn__LibYarnActiveResourceRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_active_resource_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnActiveResourceRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnActiveResourceRequestProto *
       hadoop__yarn__lib_yarn_active_resource_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_active_resource_request_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnActiveResourceRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnActiveResourceResponseProto methods */
void   hadoop__yarn__lib_yarn_active_resource_response_proto__init
                     (Hadoop__Yarn__LibYarnActiveResourceResponseProto         *message);
size_t hadoop__yarn__lib_yarn_active_resource_response_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnActiveResourceResponseProto   *message);
size_t hadoop__yarn__lib_yarn_active_resource_response_proto__pack
                     (const Hadoop__Yarn__LibYarnActiveResourceResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_active_resource_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnActiveResourceResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnActiveResourceResponseProto *
       hadoop__yarn__lib_yarn_active_resource_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_active_resource_response_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnActiveResourceResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnCreateJobRequestProto methods */
void   hadoop__yarn__lib_yarn_create_job_request_proto__init
                     (Hadoop__Yarn__LibYarnCreateJobRequestProto         *message);
size_t hadoop__yarn__lib_yarn_create_job_request_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnCreateJobRequestProto   *message);
size_t hadoop__yarn__lib_yarn_create_job_request_proto__pack
                     (const Hadoop__Yarn__LibYarnCreateJobRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_create_job_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnCreateJobRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnCreateJobRequestProto *
       hadoop__yarn__lib_yarn_create_job_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_create_job_request_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnCreateJobRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnCreateJobResponseProto methods */
void   hadoop__yarn__lib_yarn_create_job_response_proto__init
                     (Hadoop__Yarn__LibYarnCreateJobResponseProto         *message);
size_t hadoop__yarn__lib_yarn_create_job_response_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnCreateJobResponseProto   *message);
size_t hadoop__yarn__lib_yarn_create_job_response_proto__pack
                     (const Hadoop__Yarn__LibYarnCreateJobResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_create_job_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnCreateJobResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnCreateJobResponseProto *
       hadoop__yarn__lib_yarn_create_job_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_create_job_response_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnCreateJobResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnFinishJobRequestProto methods */
void   hadoop__yarn__lib_yarn_finish_job_request_proto__init
                     (Hadoop__Yarn__LibYarnFinishJobRequestProto         *message);
size_t hadoop__yarn__lib_yarn_finish_job_request_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnFinishJobRequestProto   *message);
size_t hadoop__yarn__lib_yarn_finish_job_request_proto__pack
                     (const Hadoop__Yarn__LibYarnFinishJobRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_finish_job_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnFinishJobRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnFinishJobRequestProto *
       hadoop__yarn__lib_yarn_finish_job_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_finish_job_request_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnFinishJobRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__LibYarnFinishJobResponseProto methods */
void   hadoop__yarn__lib_yarn_finish_job_response_proto__init
                     (Hadoop__Yarn__LibYarnFinishJobResponseProto         *message);
size_t hadoop__yarn__lib_yarn_finish_job_response_proto__get_packed_size
                     (const Hadoop__Yarn__LibYarnFinishJobResponseProto   *message);
size_t hadoop__yarn__lib_yarn_finish_job_response_proto__pack
                     (const Hadoop__Yarn__LibYarnFinishJobResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__lib_yarn_finish_job_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__LibYarnFinishJobResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__LibYarnFinishJobResponseProto *
       hadoop__yarn__lib_yarn_finish_job_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__lib_yarn_finish_job_response_proto__free_unpacked
                     (Hadoop__Yarn__LibYarnFinishJobResponseProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__SayHiRequestProto methods */
void   hadoop__yarn__say_hi_request_proto__init
                     (Hadoop__Yarn__SayHiRequestProto         *message);
size_t hadoop__yarn__say_hi_request_proto__get_packed_size
                     (const Hadoop__Yarn__SayHiRequestProto   *message);
size_t hadoop__yarn__say_hi_request_proto__pack
                     (const Hadoop__Yarn__SayHiRequestProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__say_hi_request_proto__pack_to_buffer
                     (const Hadoop__Yarn__SayHiRequestProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__SayHiRequestProto *
       hadoop__yarn__say_hi_request_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__say_hi_request_proto__free_unpacked
                     (Hadoop__Yarn__SayHiRequestProto *message,
                      ProtobufCAllocator *allocator);
/* Hadoop__Yarn__SayHiResponseProto methods */
void   hadoop__yarn__say_hi_response_proto__init
                     (Hadoop__Yarn__SayHiResponseProto         *message);
size_t hadoop__yarn__say_hi_response_proto__get_packed_size
                     (const Hadoop__Yarn__SayHiResponseProto   *message);
size_t hadoop__yarn__say_hi_response_proto__pack
                     (const Hadoop__Yarn__SayHiResponseProto   *message,
                      uint8_t             *out);
size_t hadoop__yarn__say_hi_response_proto__pack_to_buffer
                     (const Hadoop__Yarn__SayHiResponseProto   *message,
                      ProtobufCBuffer     *buffer);
Hadoop__Yarn__SayHiResponseProto *
       hadoop__yarn__say_hi_response_proto__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   hadoop__yarn__say_hi_response_proto__free_unpacked
                     (Hadoop__Yarn__SayHiResponseProto *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Hadoop__Yarn__LibYarnResourceProto_Closure)
                 (const Hadoop__Yarn__LibYarnResourceProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnAllocateResourceRequestProto_Closure)
                 (const Hadoop__Yarn__LibYarnAllocateResourceRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnAllocateResourceResponseProto_Closure)
                 (const Hadoop__Yarn__LibYarnAllocateResourceResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnReleaseResourceRequestProto_Closure)
                 (const Hadoop__Yarn__LibYarnReleaseResourceRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnReleaseResourceResponseProto_Closure)
                 (const Hadoop__Yarn__LibYarnReleaseResourceResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnActiveResourceRequestProto_Closure)
                 (const Hadoop__Yarn__LibYarnActiveResourceRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnActiveResourceResponseProto_Closure)
                 (const Hadoop__Yarn__LibYarnActiveResourceResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnCreateJobRequestProto_Closure)
                 (const Hadoop__Yarn__LibYarnCreateJobRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnCreateJobResponseProto_Closure)
                 (const Hadoop__Yarn__LibYarnCreateJobResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnFinishJobRequestProto_Closure)
                 (const Hadoop__Yarn__LibYarnFinishJobRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__LibYarnFinishJobResponseProto_Closure)
                 (const Hadoop__Yarn__LibYarnFinishJobResponseProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__SayHiRequestProto_Closure)
                 (const Hadoop__Yarn__SayHiRequestProto *message,
                  void *closure_data);
typedef void (*Hadoop__Yarn__SayHiResponseProto_Closure)
                 (const Hadoop__Yarn__SayHiResponseProto *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    hadoop__yarn__resource_status_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_resource_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_allocate_resource_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_allocate_resource_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_release_resource_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_release_resource_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_active_resource_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_active_resource_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_create_job_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_create_job_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_finish_job_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__lib_yarn_finish_job_response_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__say_hi_request_proto__descriptor;
extern const ProtobufCMessageDescriptor hadoop__yarn__say_hi_response_proto__descriptor;

PROTOBUF_C_END_DECLS


#endif  /* PROTOBUF_libyarn_5fprotos_2eproto__INCLUDED */
