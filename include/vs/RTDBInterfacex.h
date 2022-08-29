#pragma once
#ifdef __cplusplus
extern "C" {
#endif

int RTDBInterfaceTest();

int InitConnect(char *strParameters[], long nCount);

int ReleaseConnect();

//��������:����ʵʱ���ݲ�ѯ
int GetRTDataByTagName(const char *tagName, TagData *pTagData);

//��������:����ʵʱ���ݲ�ѯ
int GetRTDataByBatch(char *tagNames[], TagData *pTagData, long nCount);

//��������:���ԭʼ���ݲ�ѯ
int GetRawDataByTagName(ReadHiDataRequest *pReadHiDataRequest, TagData *&pTagData, long *nCount);

//��������:���������ݲ�ѯ
int GetSnapshotDataByTagName(ReadHiDataRequest *pReadHiDataRequest, TagData *pTagData);

//��������:���ͳ�����ݲ�ѯ
int GetAggregationDataByTagName(ReadHiDataRequest *pReadHiDataRequest, TagData *pTagData);

//��������:��ʷʱ�����ݲ�ѯ
int GetHistoryDataByTime(const char *tagName, long time, TagData *pTagData);

////��������:��ʷʱ�����ݲ�ѯ
//int GetHistoryDataByTimeSpan(const char *tagName, long start,long end, TagData *pTagData);

//��������:������ʷʱ�����ݲ�ѯ
int GetHisTimeDataByBatch(char *tagNames[], long time, TagData *pTagData, long nCount);

//��������:������Ϣ��ѯ
int GetTagInfoByTagName(char *tagName, TagInfo *pTagInfo);

//��������:������Ϣ��ѯ
int GetTagInfoByBatch(char *tagName[], TagInfo *pTagInfo, long nCount);

//��������:��������д�빦��
int AppendRTTagDataByTagName(InsertData *pInsertData);

//��������:��������д�빦��
int AppendRTTagDataByBatch(InsertData *pInsertData, int nCount);

//��������:�ͷź����з�����ڴ�
int RTDBFreePointer(void *p);

int SetDebug(int nDebug);

//��������:����DLL�Ļ��湦��
int SetCache(int nCache);

//��������:���DLL�Ļ�������
int ClearCache();

//��������:��ȡ���е���Ϣ
int GetNextTagsInfo(long beginPos, TagInfo *pTagInfo, long &nCount);

//��������:������ʷʱ�����ݲ�ѯ
int GetHisTimeDataByBatch(char *tagNames[], long time, TagData *pTagData, long nCount);

// �޹��������ľۺϺ���
int GetSummary(const char *tagName, long timeStart, long timeEnd, int valueType, TagData *pTagData);

// ��������ֵ���������ľۺϺ���
int GetSummaryFilter(const char *tagName, long timeStart, long timeEnd, int valueType, const char *tagNameFilter,
                     double limitLower, double limitUpper, int modeFilter, TagData *pTagData);

// ���ʽ���������µľۺϺ���
int GetSummaryFilterEX(const char *tagName, long timeStart, long timeEnd, int valueType, char *expression,
                       TagData *pTagData);

//��������:��ȡ�̶���������(�ؼ����ݲ�ѯ)
int GetMainDataByTagName(ReadHiDataRequest *pReadHiDataRequest, long nDataNum, TagData *pTagData);

//��������:�������ѯ
int QueryTagInfo(const char *tagName, const char *tagDesc, TagInfo *pTagInfo, long &nCount);

#ifdef __cplusplus
}


#endif
