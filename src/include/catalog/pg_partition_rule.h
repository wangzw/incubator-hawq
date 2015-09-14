/*-------------------------------------------------------------------------
*
* pg_partition_rule.h
*
*	  internal specifications of the partition configuration rules.
*
* Portions Copyright (c) 2008-2010, Greenplum Inc.
*-------------------------------------------------------------------------
*/
#ifndef PG_PARTITION_RULE_H
#define PG_PARTITION_RULE_H


#include "catalog/genbki.h"

/* TIDYCAT_BEGINDEF

   CREATE TABLE pg_partition_rule
   with (camelcase=PartitionRule, relid=5011, content=MASTER_ONLY)
   ( 
   paroid             oid,
   parchildrelid      oid,
   parparentrule      oid,
   parname            name,
   parisdefault       boolean,
   parruleord         smallint,
   parrangestartincl  boolean,
   parrangeendincl    boolean,
   parrangestart      text,
   parrangeend        text,
   parrangeevery      text,
   parlistvalues      text,
   parreloptions      text[],
   partemplatespace   oid
   );

   create unique index on pg_partition_rule(oid) with (indexid=5014);
   create index on pg_partition_rule(parchildrelid) with (indexid=5016);
   create index on pg_partition_rule(parchildrelid, parparentrule, parruleord) with (indexid=5015);
   create index on pg_partition_rule(paroid, parparentrule, parruleord) with (indexid=5026,indexname=pg_partition_rule_paroid_parentrule_ruleord_index);

   alter table pg_partition_rule add fk paroid on pg_partition(oid);
   alter table pg_partition_rule add fk parchildrelid on pg_class(oid);
   alter table pg_partition_rule add fk parparentrule on pg_partition_rule(oid);
   alter table pg_partition_rule add fk partemplatespace on pg_tablespace(oid);

   TIDYCAT_ENDDEF
*/

/* TIDYCAT_BEGIN_CODEGEN 

   WARNING: DO NOT MODIFY THE FOLLOWING SECTION: 
   Generated by tidycat.pl version 21.
   on Wed Nov 24 14:19:21 2010
*/


/*
 TidyCat Comments for pg_partition_rule:
  Table has an Oid column.
  Table does not have static type (only legal for pre-3.3 tables). 
  Table has TOASTable columns, but NO TOAST table.
  Table contents are only maintained on MASTER.

*/

/* ----------------
 *		pg_partition_rule definition.  cpp turns this into
 *		typedef struct FormData_pg_partition_rule
 * ----------------
 */
#define PartitionRuleRelationId	5011

CATALOG(pg_partition_rule,5011)
{
 	Oid			paroid;				
	Oid			parchildrelid;		
	Oid			parparentrule;		
	NameData	parname;			
	bool		parisdefault;		
	int2		parruleord;			
	bool		parrangestartincl;	
	bool		parrangeendincl;	
	text		parrangestart;		
	text		parrangeend;		
	text		parrangeevery;		
	text		parlistvalues;		
	text		parreloptions[1];	
	Oid			partemplatespace;	
} FormData_pg_partition_rule;


/* ----------------
 *		Form_pg_partition_rule corresponds to a pointer to a tuple with
 *		the format of pg_partition_rule relation.
 * ----------------
 */
typedef FormData_pg_partition_rule *Form_pg_partition_rule;


/* ----------------
 *		compiler constants for pg_partition_rule
 * ----------------
 */
#define Natts_pg_partition_rule						14
#define Anum_pg_partition_rule_paroid				1
#define Anum_pg_partition_rule_parchildrelid		2
#define Anum_pg_partition_rule_parparentrule		3
#define Anum_pg_partition_rule_parname				4
#define Anum_pg_partition_rule_parisdefault			5
#define Anum_pg_partition_rule_parruleord			6
#define Anum_pg_partition_rule_parrangestartincl	7
#define Anum_pg_partition_rule_parrangeendincl		8
#define Anum_pg_partition_rule_parrangestart		9
#define Anum_pg_partition_rule_parrangeend			10
#define Anum_pg_partition_rule_parrangeevery		11
#define Anum_pg_partition_rule_parlistvalues		12
#define Anum_pg_partition_rule_parreloptions		13
#define Anum_pg_partition_rule_partemplatespace		14


/* TIDYCAT_END_CODEGEN */

#endif   /* PG_PARTITION_RULE_H */
