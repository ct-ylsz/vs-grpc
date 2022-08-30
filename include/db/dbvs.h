//
// Created by ct on 2021/10/31.
//

#ifndef HIBEAT_DBVS_H
#define HIBEAT_DBVS_H
#pragma once

#include <string>
#include <vector>
#include "vs/RTDBDefine.h"
#include "log/log.h"

// 0	�������ݿ����ӳɹ�
//-1	���������쳣
//-2	���ݿ������쳣
//-3	ϵͳ�쳣
//-4	�����쳣
//-5	��㲻���ڣ����㺯����
//-6	���ݲ�����
// 1    �����쳣

enum kDbError {
    kDbOK = 0,
    kDbNetworkErr = -1,
    kDbConnectErr = -2,
    kDbSystemErr = -3,
    kDbUnknownErr = -4,
    kDbTagNotExist = -5,
    kDbValueNotExist = -6,
    kArgBad = 1,
    kDbConfigErr = 2
};

//valueType ��1��Сֵ��2���ֵ��3����ƽ��ֵ��
// 4ʱ���Ȩƽ��ֵ��5����ֵ��6�ۻ�ֵ��ֱ���ۼӣ���
// 7��ֵ������ֵ-��ʼֵ����8��ʼֵ,9����ֵ��99��Ч��ֵ����

enum kValueType {
    kMin = 1,
    kMax = 2,
    kAvg = 3,
    kTimeAvg = 4,
    kIntegralValue = 5,
    kSumValue = 6,
    kSubValue = 7,
    kStartValue = 8,
    kEndValue = 9,
    kCount = 99
};

struct DbError {
    int err_code = 0;
    std::string err_msg = "success";
};


class DbVs {
public:
    static inline Logger *log_ = new Logger();

    static inline std::once_flag once_ = std::once_flag();

    static inline std::once_flag once2_ = std::once_flag();

    static int Init(const std::string &dll_path);

    // ������ݿ�����
    static DbError DbConnect(char *dllPath, char *configPath, char *opt1, char *opt2);

    // �ͷ����ݿ�����
    static DbError DbReleaseConnect();

    // ����ʵʱ���ݲ�ѯ
    static DbError TagRealTimeDataGetByName(const char *tagName, TagData *data);

    // ��ҳ��ȡ��ǩ��Ϣ
    static DbError TagNamesGetByCount(long beginPos, std::vector<TagInfo *> *tags, long &nCount);

    // ��ҳ��ȡ�б�
    static DbError TagListByCount(long beginPos, std::vector<TagInfo> *tags, long &nCount);

    // ��ȡȫ���б�
    static DbError TagListAll(std::vector<TagInfo> *tags);

    // ��ȡ���б�ǩ��Ϣ
    static DbError TagsNameGet(std::vector<TagInfo *> *tags);

    // ��ȡ��������ֶ�
    static DbError TagDescInfoGet(char *tagName, TagInfo *pTagInfo);

    // ��ȡ���в�������ֶ�
    static DbError TagsDescInfoGet(std::vector<TagInfo *> tags);

    // ��ȡ����ֵ
    static DbError
    TagGetAggregation(const std::string &tag_name, long start, long end, int req_type, int t_period, TagData *tagData);

    // ��ȡʱ�������
    static DbError
    TagValuesGet(const std::string &tag_name, long start, long end, long &count, std::vector<TagData> *tagValues);

    // ��ȡʱ�������
    static DbError
    TagValuesGet(ReadHiDataRequest req, long &count, std::vector<TagData> *tagValues);

    //valueType ��1��Сֵ��2���ֵ��3����ƽ��ֵ��4ʱ���Ȩƽ��ֵ��5����ֵ��6�ۻ�ֵ��ֱ���ۼӣ���7��ֵ������ֵ-��ʼֵ����8��ʼֵ,9����ֵ��99��Ч��ֵ����
    // ��ȡ���ƽ��ֵ
    static DbError TagAvgValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ�����Сֵ
    static DbError TagMinValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ������ֵ
    static DbError TagMaxValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ����Ȩƽ��ֵ
    static DbError TagTimeAvgValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ������ֵ
    static DbError TagIntegralValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ����ۻ�ֵ
    static DbError TagSumValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ����ֵ
    static DbError TagSubValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ��㿪ʼֵ
    static DbError TagStartValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ������ֵ
    static DbError TagEndValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ�����Ч����
    static DbError TagValidCount(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ����ֵ
    static DbError TagDescGet(const std::string &tag_name, long start, long end, TagData *tagData, int vType);

    // ��ȡ��ʷʱ��
    static DbError HistoryTime(const std::string &tag_name, long time, TagData *tagData);

    // ��ȡ��ʷʱ���
    static DbError HistoryTimeSpan(const std::string &tag_name, long start, long end, TagData *tagData);

    // ��ȡ��ʷ����ֵ
    static DbError TagSnapshotByName(ReadHiDataRequest *req, std::vector<TagData> *tagValues);

    // ������ȡ��ʷ����ֵ
    static DbError GetRTDataByBatch(std::vector<std::string> *names, std::vector<TagData> *tagValues);


    // ��������
    static DbError TagDataInsert(InsertData *data, int count);
};


#endif //HIBEAT_DBVS_H
