/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TD_INDEX_H_
#define _TD_INDEX_H_

#include "os.h"
#include "tarray.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SIndex SIndex;
typedef struct SIndexTerm SIndexTerm;
typedef struct SIndexOpts SIndexOpts;
typedef struct SIndexMultiTermQuery SIndexMultiTermQuery;
typedef struct SArray               SIndexMultiTerm;

typedef enum  {
   ADD_VALUE,    // add index colume value   
   DEL_VALUE,    // delete index column value  
   UPDATE_VALUE, // update index column value 
   ADD_INDEX,    // add index on specify column
   DROP_INDEX,   // drop existed index 
   DROP_SATBLE   // drop stable 
} SIndexOperOnColumn;

typedef enum  { MUST = 0, SHOULD = 1, NOT = 2 } EIndexOperatorType;
typedef enum  { QUERY_TERM = 0, QUERY_PREFIX = 1, QUERY_SUFFIX = 2,QUERY_REGEX = 3} EIndexQueryType;
/*
 * @param: oper 
 *
*/
SIndexMultiTermQuery *indexMultiTermQueryCreate(EIndexOperatorType oper);
void            indexMultiTermQueryDestroy(SIndexMultiTermQuery *pQuery);
int             indexMultiTermQueryAdd(SIndexMultiTermQuery *pQuery, SIndexTerm *term, EIndexQueryType type);
/* 
 * @param:    
 * @param:
 */
SIndex* indexOpen(SIndexOpts *opt, const char *path);
void  indexClose(SIndex *index);
int   indexPut(SIndex *index,    SIndexMultiTerm *terms, int uid);
int   indexDelete(SIndex *index, SIndexMultiTermQuery *query); 
int   indexSearch(SIndex *index, SIndexMultiTermQuery *query, SArray *result);
int   indexRebuild(SIndex *index, SIndexOpts *opt);
/*
 * @param
 * @param
 */
SIndexMultiTerm *indexMultiTermCreate(); 
int indexMultiTermAdd(SIndexMultiTerm  *terms, SIndexTerm *term);
void indexMultiTermDestroy(SIndexMultiTerm *terms);
/*
 * @param: 
 * @param:
 */
SIndexOpts *indexOptsCreate();
void       indexOptsDestroy(SIndexOpts *opts);


/*
 * @param:
 * @param:
 */

SIndexTerm *indexTermCreate(int64_t suid, SIndexOperOnColumn operType, uint8_t colType, 
                            const char *colName, int32_t nColName, const char *colVal, int32_t nColVal);
void        indexTermDestroy(SIndexTerm *p);


#ifdef __cplusplus
}
#endif

#endif /*_TD_INDEX_H_*/
