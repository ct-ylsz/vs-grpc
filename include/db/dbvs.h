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

// 0	建立数据库连接成功
//-1	网络连接异常
//-2	数据库连接异常
//-3	系统异常
//-4	其他异常
//-5	测点不存在（单点函数）
//-6	数据不存在
// 1    参数异常

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

//valueType ：1最小值，2最大值，3算术平均值，
// 4时间加权平均值，5积分值，6累积值（直接累加），
// 7差值（结束值-开始值），8开始值,9结束值，99有效数值个数

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

    // 检测数据库连接
    static DbError DbConnect(char *dllPath, char *configPath, char *opt1, char *opt2);

    // 释放数据库连接
    static DbError DbReleaseConnect();

    // 单点实时数据查询
    static DbError TagRealTimeDataGetByName(const char *tagName, TagData *data);

    // 分页获取标签信息
    static DbError TagNamesGetByCount(long beginPos, std::vector<TagInfo *> *tags, long &nCount);

    // 分页获取列表
    static DbError TagListByCount(long beginPos, std::vector<TagInfo> *tags, long &nCount);

    // 获取全量列表
    static DbError TagListAll(std::vector<TagInfo> *tags);

    // 获取所有标签信息
    static DbError TagsNameGet(std::vector<TagInfo *> *tags);

    // 获取测点描述字段
    static DbError TagDescInfoGet(char *tagName, TagInfo *pTagInfo);

    // 获取所有测点描述字段
    static DbError TagsDescInfoGet(std::vector<TagInfo *> tags);

    // 获取特征值
    static DbError
    TagGetAggregation(const std::string &tag_name, long start, long end, int req_type, int t_period, TagData *tagData);

    // 获取时间段数据
    static DbError
    TagValuesGet(const std::string &tag_name, long start, long end, long &count, std::vector<TagData> *tagValues);

    // 获取时间段数据
    static DbError
    TagValuesGet(ReadHiDataRequest req, long &count, std::vector<TagData> *tagValues);

    //valueType ：1最小值，2最大值，3算术平均值，4时间加权平均值，5积分值，6累积值（直接累加），7差值（结束值-开始值），8开始值,9结束值，99有效数值个数
    // 获取测点平均值
    static DbError TagAvgValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点最小值
    static DbError TagMinValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点最大值
    static DbError TagMaxValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点加权平均值
    static DbError TagTimeAvgValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点积分值
    static DbError TagIntegralValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点累积值
    static DbError TagSumValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点差值
    static DbError TagSubValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点开始值
    static DbError TagStartValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点结束值
    static DbError TagEndValue(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取测点有效个数
    static DbError TagValidCount(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取特征值
    static DbError TagDescGet(const std::string &tag_name, long start, long end, TagData *tagData, int vType);

    // 获取历史时间
    static DbError HistoryTime(const std::string &tag_name, long time, TagData *tagData);

    // 获取历史时间段
    static DbError HistoryTimeSpan(const std::string &tag_name, long start, long end, TagData *tagData);

    // 获取历史快照值
    static DbError TagSnapshotByName(ReadHiDataRequest *req, std::vector<TagData> *tagValues);

    // 批量获取历史快照值
    static DbError GetRTDataByBatch(std::vector<std::string> *names, std::vector<TagData> *tagValues);


    // 插入数据
    static DbError TagDataInsert(InsertData *data, int count);
};


#endif //HIBEAT_DBVS_H
