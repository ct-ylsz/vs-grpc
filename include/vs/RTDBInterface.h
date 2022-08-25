
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RTDBINTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RTDBINTERFACE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef RTDBINTERFACE_EXPORTS
#define RTDBINTERFACE_API __declspec(dllexport)
#else
#define RTDBINTERFACE_API __declspec(dllimport)
#endif

// This class is exported from the RTDBInterface.dll
class RTDBINTERFACE_API CRTDBInterface {
public:
	CRTDBInterface(void);
	// TODO: add your methods here.
};


RTDBINTERFACE_API int InitConnect(char* strParameters[],long nCount);

RTDBINTERFACE_API int ReleaseConnect();

//函数功能:单点实时数据查询
RTDBINTERFACE_API int GetRTDataByTagName(const char* tagName,TagData * pTagData );

//函数功能:批量实时数据查询
RTDBINTERFACE_API int GetRTDataByBatch(char* tagNames[],TagData * pTagData,long nCount);

//函数功能:测点原始数据查询
RTDBINTERFACE_API int GetRawDataByTagName(ReadHiDataRequest * pReadHiDataRequest, TagData * & pTagData,long * nCount);

//函数功能:测点快照数据查询
RTDBINTERFACE_API int GetSnapshotDataByTagName(ReadHiDataRequest * pReadHiDataRequest, TagData *  pTagData);

//函数功能:测点统计数据查询
RTDBINTERFACE_API int GetAggregationDataByTagName(ReadHiDataRequest * pReadHiDataRequest, TagData * pTagData);

//函数功能:历史时刻数据查询
RTDBINTERFACE_API int GetHistoryDataByTime(const char * tagName,long time, TagData *pTagData);

//函数功能:批量历史时刻数据查询
RTDBINTERFACE_API int GetHisTimeDataByBatch(char* tagNames[],long time,TagData * pTagData,long nCount);

//函数功能:单点信息查询
RTDBINTERFACE_API int GetTagInfoByTagName(char* tagName,TagInfo *pTagInfo);

//函数功能:批量信息查询
RTDBINTERFACE_API int GetTagInfoByBatch(char* tagName[],TagInfo *pTagInfo,long nCount);

//函数功能:单点数据写入功能
RTDBINTERFACE_API int AppendRTTagDataByTagName(InsertData *pInsertData);

//函数功能:批量数据写入功能
RTDBINTERFACE_API int AppendRTTagDataByBatch(InsertData *pInsertData,int nCount);

//函数功能:释放函数中分配的内存
RTDBINTERFACE_API int RTDBFreePointer(void *p);

RTDBINTERFACE_API int SetDebug(int nDebug);

//函数功能:设置DLL的缓存功能
RTDBINTERFACE_API int SetCache(int nCache);

//函数功能:清除DLL的缓存数据
RTDBINTERFACE_API int ClearCache();

//函数功能:获取所有点信息
RTDBINTERFACE_API int GetNextTagsInfo(long beginPos,TagInfo *pTagInfo,long &nCount);

//函数功能:批量历史时刻数据查询
RTDBINTERFACE_API int GetHisTimeDataByBatch(char* tagNames[],long time,TagData * pTagData,long nCount);

// 无过滤条件的聚合函数
RTDBINTERFACE_API int GetSummary(const char* tagName, long timeStart, long timeEnd, int valueType,TagData * pTagData);

// 自身测点数值过滤条件的聚合函数
RTDBINTERFACE_API int GetSummaryFilter(const char* tagName, long timeStart, long timeEnd, int valueType,const char* tagNameFilter, double limitLower, double limitUpper, int modeFilter,TagData * pTagData);

// 表达式过滤条件下的聚合函数
RTDBINTERFACE_API int GetSummaryFilterEX(const char* tagName, long timeStart, long timeEnd, int valueType, char* expression,TagData * pTagData);

//函数功能:获取固定个数数据(关键数据查询)
RTDBINTERFACE_API int GetMainDataByTagName(ReadHiDataRequest * pReadHiDataRequest, long nDataNum,TagData *  pTagData);

//函数功能:批量点查询
RTDBINTERFACE_API int QueryTagInfo(const char* tagName,const char* tagDesc,TagInfo *pTagInfo,long &nCount);

//函数功能:获取服务器时间
RTDBINTERFACE_API long GetUTCTime();




