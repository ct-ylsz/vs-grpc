#pragma once
#ifdef __cplusplus
extern "C" {
#endif

int RTDBInterfaceTest();

int InitConnect(char *strParameters[], long nCount);

int ReleaseConnect();

//函数功能:单点实时数据查询
int GetRTDataByTagName(const char *tagName, TagData *pTagData);

//函数功能:批量实时数据查询
int GetRTDataByBatch(char *tagNames[], TagData *pTagData, long nCount);

//函数功能:测点原始数据查询
int GetRawDataByTagName(ReadHiDataRequest *pReadHiDataRequest, TagData *&pTagData, long *nCount);

//函数功能:测点快照数据查询
int GetSnapshotDataByTagName(ReadHiDataRequest *pReadHiDataRequest, TagData *pTagData);

//函数功能:测点统计数据查询
int GetAggregationDataByTagName(ReadHiDataRequest *pReadHiDataRequest, TagData *pTagData);

//函数功能:历史时刻数据查询
int GetHistoryDataByTime(const char *tagName, long time, TagData *pTagData);

////函数功能:历史时刻数据查询
//int GetHistoryDataByTimeSpan(const char *tagName, long start,long end, TagData *pTagData);

//函数功能:批量历史时刻数据查询
int GetHisTimeDataByBatch(char *tagNames[], long time, TagData *pTagData, long nCount);

//函数功能:单点信息查询
int GetTagInfoByTagName(char *tagName, TagInfo *pTagInfo);

//函数功能:批量信息查询
int GetTagInfoByBatch(char *tagName[], TagInfo *pTagInfo, long nCount);

//函数功能:单点数据写入功能
int AppendRTTagDataByTagName(InsertData *pInsertData);

//函数功能:批量数据写入功能
int AppendRTTagDataByBatch(InsertData *pInsertData, int nCount);

//函数功能:释放函数中分配的内存
int RTDBFreePointer(void *p);

int SetDebug(int nDebug);

//函数功能:设置DLL的缓存功能
int SetCache(int nCache);

//函数功能:清除DLL的缓存数据
int ClearCache();

//函数功能:获取所有点信息
int GetNextTagsInfo(long beginPos, TagInfo *pTagInfo, long &nCount);

//函数功能:批量历史时刻数据查询
int GetHisTimeDataByBatch(char *tagNames[], long time, TagData *pTagData, long nCount);

// 无过滤条件的聚合函数
int GetSummary(const char *tagName, long timeStart, long timeEnd, int valueType, TagData *pTagData);

// 自身测点数值过滤条件的聚合函数
int GetSummaryFilter(const char *tagName, long timeStart, long timeEnd, int valueType, const char *tagNameFilter,
                     double limitLower, double limitUpper, int modeFilter, TagData *pTagData);

// 表达式过滤条件下的聚合函数
int GetSummaryFilterEX(const char *tagName, long timeStart, long timeEnd, int valueType, char *expression,
                       TagData *pTagData);

//函数功能:获取固定个数数据(关键数据查询)
int GetMainDataByTagName(ReadHiDataRequest *pReadHiDataRequest, long nDataNum, TagData *pTagData);

//函数功能:批量点查询
int QueryTagInfo(const char *tagName, const char *tagDesc, TagInfo *pTagInfo, long &nCount);

#ifdef __cplusplus
}


#endif
