/*-------------------------------------------------------------------------
 *
 * pg_filesystem.h
 *    an user defined filesystem table
 *
 * Copyright (c) 2011, Greenplum Inc.
 *
 * $Id: $
 * $Change: $
 * $DateTime: $
 * $Author: $
 *-------------------------------------------------------------------------
 */
#ifndef PG_FILESYSTEM_H
#define PG_FILESYSTEM_H

#include "catalog/genbki.h"
#include "nodes/pg_list.h"
#include "utils/acl.h"

/* TIDYCAT_BEGINDEF

  CREATE TABLE pg_filesystem
  with (camelcase=FileSystem, shared=true, oid=true, relid=6112, reltype_oid=6113, toast_oid=6114, toast_index=6115, toast_reltype=6116)
  (
   fsysname             name, -- filesystem name
   fsysconnfn			name,  -- connect
   fsysdisconnfn		name,  -- disconnect
   fsysopenfn			name,  -- open
   fsysclosefn			name,  -- close
   fsysseekfn			name,
   fsystellfn			name,
   fsysreadfn			name,
   fsyswritefn			name,
   fsysflushfn			name,
   fsysdeletefn         name,
   fsyschmodfn          name,
   fsysmkdirfn          name,
   fsystruncatefn       name,
   fsysgetpathinfofn    name,
   fsysfreefileinfofn   name,
   fsyslibfile          text,
   fsysowner            Oid,  -- owner
   fsystrusted	        bool, --
   fsysacl              aclitem[]
   );
   
   create unique index on pg_filesystem(oid) with (indexid=7183);
   create unique index on pg_filesystem(fsysname) with (indexid=7184);

   TIDYCAT_ENDDEF
*/
/* TIDYCAT_BEGIN_CODEGEN 

   WARNING: DO NOT MODIFY THE FOLLOWING SECTION: 
   Generated by ./tidycat.pl version 34
   on Wed Jan 23 13:04:28 2013
*/


/*
 TidyCat Comments for pg_filesystem:
  Table is shared, so catalog.c:IsSharedRelation is updated.
  Table has an Oid column.
  Table has static type (see pg_types.h).
  Table has TOASTable columns, and TOAST table has static type.

*/

/* ----------------
 *		pg_filesystem definition.  cpp turns this into
 *		typedef struct FormData_pg_filesystem
 * ----------------
 */
#define FileSystemRelationId	6112

CATALOG(pg_filesystem,6112) BKI_SHARED_RELATION
{
	NameData	fsysname;			/* filesystem name */
	NameData	fsysconnfn;			/* connect */
	NameData	fsysdisconnfn;		/* disconnect */
	NameData	fsysopenfn;			/* open */
	NameData	fsysclosefn;		/* close */
	NameData	fsysseekfn;			
	NameData	fsystellfn;			
	NameData	fsysreadfn;			
	NameData	fsyswritefn;		
	NameData	fsysflushfn;		
	NameData	fsysdeletefn;		
	NameData	fsyschmodfn;		
	NameData	fsysmkdirfn;		
	NameData	fsystruncatefn;		
	NameData	fsysgetpathinfofn;	
	NameData	fsysfreefileinfofn;	
	text		fsyslibfile;		
	Oid			fsysowner;			/* owner */
	bool		fsystrusted;		/* */
	aclitem		fsysacl[1];			
} FormData_pg_filesystem;


/* ----------------
 *		Form_pg_filesystem corresponds to a pointer to a tuple with
 *		the format of pg_filesystem relation.
 * ----------------
 */
typedef FormData_pg_filesystem *Form_pg_filesystem;


/* ----------------
 *		compiler constants for pg_filesystem
 * ----------------
 */
#define Natts_pg_filesystem						20
#define Anum_pg_filesystem_fsysname				1
#define Anum_pg_filesystem_fsysconnfn			2
#define Anum_pg_filesystem_fsysdisconnfn		3
#define Anum_pg_filesystem_fsysopenfn			4
#define Anum_pg_filesystem_fsysclosefn			5
#define Anum_pg_filesystem_fsysseekfn			6
#define Anum_pg_filesystem_fsystellfn			7
#define Anum_pg_filesystem_fsysreadfn			8
#define Anum_pg_filesystem_fsyswritefn			9
#define Anum_pg_filesystem_fsysflushfn			10
#define Anum_pg_filesystem_fsysdeletefn			11
#define Anum_pg_filesystem_fsyschmodfn			12
#define Anum_pg_filesystem_fsysmkdirfn			13
#define Anum_pg_filesystem_fsystruncatefn		14
#define Anum_pg_filesystem_fsysgetpathinfofn	15
#define Anum_pg_filesystem_fsysfreefileinfofn	16
#define Anum_pg_filesystem_fsyslibfile			17
#define Anum_pg_filesystem_fsysowner			18
#define Anum_pg_filesystem_fsystrusted			19
#define Anum_pg_filesystem_fsysacl				20


/* TIDYCAT_END_CODEGEN */


/*
 * HDFS default options.
 */
#define FS_DEFAULT_REPLICA_NUM (0)
#define FS_MAX_REPLICA_NUM (10)

/*
 * Different type of functions that can be 
 * specified for a given file system.
 */
typedef enum FileSystemFuncType
{
	FSYS_FUNC_CONNECT,
	FSYS_FUNC_DISCONNECT, // nouse
	FSYS_FUNC_OPEN,
	FSYS_FUNC_CLOSE,
	FSYS_FUNC_SEEK,
	FSYS_FUNC_TELL,
	FSYS_FUNC_READ,
	FSYS_FUNC_WRITE,
	FSYS_FUNC_SYNC, // reopen
	FSYS_FUNC_DELETE,
	FSYS_FUNC_CHMOD,
	FSYS_FUNC_MKDIR,
	FSYS_FUNC_TRUNCATE,
	FSYS_FUNC_GETPATHINFO,
	FSYS_FUNC_FREEFILEINFO,
	FSYS_FUNC_TOTALNUM
} FileSystemFuncType;

extern Oid
FileSystemCreateWithOid(const char		   *protocolName,
						Oid					protNamespace,
						List			   *funcNames[],
						int					funcNum,
						const char		   *fsysLibFile,
						Oid					fsysOid,
						bool   				trusted);

extern void
FileSystemDeleteByOid(Oid	fsysOid);

extern Oid
LookupFileSystemFunction(const char *fsys_name, 
						  FileSystemFuncType prot_type,
						  bool error);

extern Oid
LookupFileSystemOid(const char *fsys_name, bool error_if_missing);

extern char *
FileSystemGetNameByOid(Oid	fsysOid);

extern char *
fsys_func_type_to_name(FileSystemFuncType ftype);

extern int
fsys_func_type_to_attnum(FileSystemFuncType ftype);

#endif
