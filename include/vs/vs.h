#pragma once

#include <cstdlib>
#include <cstdio>
#include "RTDBDefine.h"

typedef int (*pInitConnect)(char *strParameters[], long nCount);

typedef int (*pReleaseConnect)();

typedef int (*pGetRTDataByTagName)(const char *tagName, TagData *pTagData);

typedef int (*pGetRTDataByBatch)(char *tagNames[], TagData *pTagData, long nCount);

typedef int (*pGetRawDataByTagName)(ReadHiDataRequest *pReadHiDataRequest, TagData *&pTagData, long *nCount);

typedef int (*pGetMainDataByTagName)(ReadHiDataRequest *pReadHiDataRequest, long nDataNum, TagData *pTagData);

typedef int (*pGetSnapshotDataByTagName)(ReadHiDataRequest *pReadHiDataRequest, TagData *pTagData);

typedef int (*pGetAggregationDataByTagName)(ReadHiDataRequest *pReadHiDataRequest, TagData *pTagData);

typedef int (*pGetHistoryDataByTime)(const char *tagName, long time, TagData *pTagData);

typedef int (*pGetHistoryDataByTimeSpan)(const char *tagName, long strtime, long endtime, TagData *pTagData);

typedef int (*pGetTagInfoByTagName)(char *tagName, TagInfo *pTagInfo);

typedef int (*pGetTagInfoByBatch)(char *tagName[], TagInfo *pTagInfo, long nCount);

typedef int (*pAppendRTTagDataByTagName)(InsertData *pInsertData);

typedef int (*pAppendRTTagDataByBatch)(InsertData *pInsertData, int nCount);

typedef int (*pGetNextTagsInfo)(long beginPos, TagInfo *pTagInfo, long &nCount);

typedef int (*pAppendRTTagDataByTagName)(InsertData *pInsertData);

typedef int (*pGetSummary)(const char *tagName, long timeStart, long timeEnd, int valueType, TagData *pTagData);

typedef int (*pGetSummaryFilter)(const char *tagName, long timeStart, long timeEnd, int valueType,
                                 const char *tagNameFilter, double limitLower, double limitUpper, int modeFilter,
                                 TagData *pTagData);

typedef int (*pGetSummaryFilterEx)(const char *tagName, long timeStart, long timeEnd, int valueType, char *expression,
                                   TagData *pTagData);

typedef int (*pRTDBFreePointer)(void *p);


//typedef bool (*pOPenDataBase)(struct DataBasePara DataBase, struct RightPara iRight);
//pOPenDataBasePointer m_OPenDataBase;
