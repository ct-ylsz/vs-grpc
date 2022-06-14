//
// Created by ct on 2021/11/2.
//
#include <string>
#include <cstring>
#include <iostream>
#include "db/dbvs.h"
#include "vs/vs.h"
#include <boost/format.hpp>

#ifdef WIN32

#include <windows.h>
pInitConnect m_InitConnect;
pReleaseConnect m_ReleaseConnect;
pGetRTDataByTagName m_GetRTDataByTagName;
pGetRTDataByBatch m_GetRTDataByBatch;
pGetRawDataByTagName m_GetRawDataByTagName;
pGetSnapshotDataByTagName m_GetSnapshotDataByTagName;
pGetAggregationDataByTagName m_GetAggregationDataByTag;
pGetHistoryDataByTime m_GetHistoryDataByTime;
pGetHistoryDataByTimeSpan m_GetHistoryDataByTimeSpan;
pGetTagInfoByTagName m_GetTagInfoByTagName;
pGetTagInfoByBatch m_GetTagInfoByBatch;
pAppendRTTagDataByTagName m_AppendRTTagDataByTagName;
pRTDBFreePointer m_RTDBFreePointer;
pGetSummary m_GetSummary;
pAppendRTTagDataByTagName m_pInsertData;
pGetNextTagsInfo m_pGetNextTagInfo;
pAppendRTTagDataByBatch m_AppendRTTagDataByBatch;
pGetAggregationDataByTagName m_GetAggregationDataByTagName;
pGetSummaryFilter m_GetSummaryFilter;
pGetSummaryFilterEx m_GetSummaryFilterEx;
#else
#include "vs/RTDBInterface.h"
#endif

int DbVs::Init(const std::string &dll_path) {
#ifdef WIN32
    int err = 0;
    log_->Debug((boost::format("dll_path : %1%") % dll_path).str());
    std::call_once(once_, [](const std::string &dll, int *err) {
        HINSTANCE hInst;
        hInst = LoadLibrary(TEXT((dll + "RTDBInterface.dll").c_str()));
        if (!hInst) {
            log_->Error((boost::format("can not load dll !")).str());
            return -1;
        } else {
            m_InitConnect = (pInitConnect) GetProcAddress(hInst, "InitConnect");
            m_pGetNextTagInfo = (pGetNextTagsInfo) GetProcAddress(hInst, "GetNextTagsInfo");
            m_ReleaseConnect = (pReleaseConnect) GetProcAddress(hInst, "ReleaseConnect");
            m_GetRTDataByTagName = (pGetRTDataByTagName) GetProcAddress(hInst, "GetRTDataByTagName");
            m_GetRTDataByBatch = (pGetRTDataByBatch) GetProcAddress(hInst, "GetRTDataByBatch");
            m_GetRawDataByTagName = (pGetRawDataByTagName) GetProcAddress(hInst, "GetRawDataByTagName");
            m_GetSnapshotDataByTagName = (pGetSnapshotDataByTagName) GetProcAddress(hInst, "GetSnapshotDataByTagName");
            m_GetHistoryDataByTime = (pGetHistoryDataByTime) GetProcAddress(hInst, "GetHistoryDataByTime");
            m_GetTagInfoByTagName = (pGetTagInfoByTagName) GetProcAddress(hInst, "GetTagInfoByTagName");
            m_GetTagInfoByBatch = (pGetTagInfoByBatch) GetProcAddress(hInst, "GetTagInfoByBatch");
            m_AppendRTTagDataByTagName = (pAppendRTTagDataByTagName) GetProcAddress(hInst, "AppendRTTagDataByTagName");
            m_AppendRTTagDataByBatch = (pAppendRTTagDataByBatch) GetProcAddress(hInst, "AppendRTTagDataByBatch");
            m_RTDBFreePointer = (pRTDBFreePointer) GetProcAddress(hInst, "RTDBFreePointer");
            m_AppendRTTagDataByTagName = (pAppendRTTagDataByTagName) GetProcAddress(hInst, "AppendRTTagDataByTagName");
            m_GetAggregationDataByTagName = (pGetAggregationDataByTagName) GetProcAddress(hInst,
                                                                                          "GetAggregationDataByTagName");
            m_GetSummaryFilter = (pGetSummaryFilter) GetProcAddress(hInst, "GetSummaryFilter");
            m_GetSummaryFilterEx = (pGetSummaryFilterEx) GetProcAddress(hInst, "GetSummaryFilterEx");
            m_AppendRTTagDataByTagName = (pAppendRTTagDataByTagName) GetProcAddress(hInst, "AppendRTTagDataByTagName");
        }
        return 0;
    }, dll_path, &err);
    return err;
#else
    return 0;
#endif

}

void GetErr(DbError *err) {
    switch (err->err_code) {
        case kDbOK:
            err->err_msg = "success";
            break;
        case kDbNetworkErr:
            err->err_msg = "network is abnormal";
            break;
        case kDbConnectErr:
            err->err_msg = "database is abnormal";
            break;
        case kDbSystemErr:
            err->err_msg = "system error";
            break;
        case kDbUnknownErr:
            err->err_msg = "db unknow error";
            break;
        case kDbTagNotExist:
            err->err_msg = "tag not exist";
            break;
        case kDbValueNotExist:
            err->err_msg = "data no exist";
            break;
        case kArgBad:
            err->err_msg = "arg is invalid";
            break;
        case kDbConfigErr:
            err->err_msg = "init dll failed ";
            break;
        default:
            err->err_msg = "unkonw error";
            break;
    }
}

DbError DbVs::DbConnect(char *dllPath, char *configPath, char *opt1, char *opt2) {
    DbError err;
    auto errNo = Init(dllPath);
    if (errNo != 0) {
        err.err_code = kDbConfigErr;
        GetErr(&err);
        return err;
    }
    if (dllPath == nullptr || configPath == nullptr) {
        err.err_code = kArgBad;
        GetErr(&err);
        return err;
    }
    char *strParameters[4];
    strParameters[0] = dllPath;
    strParameters[1] = configPath;
    strParameters[2] = opt1;
    strParameters[3] = opt2;
#ifdef WIN32
    err.err_code = m_InitConnect(strParameters, 4);
//    std::call_once(once2_, [](char *para[4], DbError *err1) {
//        err1->err_code = m_InitConnect(para, 4);
//    }, strParameters, &err);
#else
    err.err_code = InitConnect(strParameters,4);
#endif
    GetErr(&err);
    return err;
}

DbError DbVs::DbReleaseConnect() {
    DbError err;
#ifdef WIN32
    err.err_code = m_ReleaseConnect();
#else
    err.err_code = ReleaseConnect();
#endif
    GetErr(&err);
    return err;
}

DbError DbVs::TagRealTimeDataGetByName(const char *tagName, TagData *data) {
    DbError err;
    if (tagName == nullptr || data == nullptr) {
        err.err_code = 1;
        GetErr(&err);
        return err;
    }
#ifdef WIN32
    err.err_code = m_GetRTDataByTagName(tagName, data);
#else
    err.err_code = GetRTDataByTagName(tagName,data);
#endif
    GetErr(&err);
    return err;
}

DbError DbVs::TagListByCount(long beginPos, std::vector<TagInfo> *tags, long &nCount) {
    DbError err;
    if (tags == nullptr || nCount == 0) {
        err.err_code = 1;
        GetErr(&err);
        return err;
    }
    auto *tag = new TagInfo[nCount];
#ifdef WIN32
    err.err_code = m_pGetNextTagInfo(beginPos, tag, nCount);
#else
    err.err_code = GetNextTagsInfo(beginPos,tag,nCount);
#endif
    if (err.err_code != 0) {
        delete[] tag;
        GetErr(&err);
        return err;
    }

    for (int i = 0; i < nCount; i++) {
        tags->push_back(tag[i]);
    }
    delete[] tag;
    return err;
}

DbError DbVs::TagNamesGetByCount(long beginPos, std::vector<TagInfo *> *tags, long &nCount) {
    DbError err;
    if (tags == nullptr || nCount == 0) {
        err.err_code = 1;
        GetErr(&err);
        return err;
    }
    auto *tag = new TagInfo[nCount];
#ifdef WIN32
    err.err_code = m_pGetNextTagInfo(beginPos, tag, nCount);
#else
    err.err_code = GetNextTagsInfo(beginPos,tag,nCount);
#endif
    if (err.err_code != 0) {
        delete[] tag;
        GetErr(&err);
        return err;
    }

    for (int i = 0; i < nCount; i++) {
        tags->push_back(&tag[i]);
    }

    return err;
}

DbError DbVs::TagListAll(std::vector<TagInfo> *tags) {
    DbError err;
    long count = 10000;
    log_->Info("start to get list ...");
    int index = 0;
    while ((count == 10000)) {
        auto *tag = new TagInfo[10000];
#ifdef WIN32
        err.err_code = m_pGetNextTagInfo(index, tag, (long &) count);
#else
        err.err_code = GetNextTagsInfo(index, tag, (long &) count);
#endif
        if (err.err_code != 0) {
            delete[] tag;
            return err;
        }
        //判断与进行扩容
        for (int i = 0; i < count; i++) {
            tags->push_back(tag[i]);
        }
        delete[] tag;
        index += count;
    }
    return err;
}

DbError DbVs::TagsNameGet(std::vector<TagInfo *> *tags) {
    DbError err;
    long count = 10000;
    log_->Info("start to collect data");
    int index = 0;
    while ((count == 10000)) {
        auto *tag = new TagInfo[10000];
#ifdef WIN32
        err.err_code = m_pGetNextTagInfo(index, tag, (long &) count);
#else
        err.err_code = GetNextTagsInfo(index, tag, (long &) count);
#endif
        if (err.err_code != 0) {
            delete[] tag;
            continue;
        }
        //判断与进行扩容
        for (int i = 0; i < count; i++) {
            tags->push_back(&tag[i]);
        }

        if (count < 10000) {
            break;
        }
        index += count;
    }

    std::cout << tags->size() << std::endl;
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagDescInfoGet(char *tagName, TagInfo *pTagInfo) {
    DbError err;
    if (pTagInfo == nullptr) {
        err.err_code = 1;
        GetErr(&err);
        return err;
    }
#ifdef WIN32
    err.err_code = m_GetTagInfoByTagName(tagName, pTagInfo);
#else
    err.err_code = GetTagInfoByTagName(tagName,pTagInfo);
#endif

    GetErr(&err);
    return err;
}


DbError DbVs::TagsDescInfoGet(std::vector<TagInfo *> tags) {
    DbError err;

    long count = 2000;
    count = 2000;
    std::cout << "开始获取数据" << std::endl;
    int index = 0;
    long sumCount = 0;
    while ((count = 2000)) {
        auto *tag = new TagInfo[2000];
#ifdef WIN32
        err.err_code = m_pGetNextTagInfo(index, tag, (long &) count);
#else
        err.err_code = GetNextTagsInfo(index, tag, (long &) count);
#endif

        if (err.err_code != 0) {
            std::cout << "报错了" << std::endl;
        }
        for (int i = 0; i < count; i++) {
            tags.push_back(&tag[i]);
        }
        if (count < 2000) {
            break;
        }
        index += count;
    }
    std::cout << tags.size() << std::endl;
    std::cout << "结束" << std::endl;
    return err;
}

DbError
DbVs::TagValuesGet(const std::string &tag_name, long start, long end, long &count, std::vector<TagData> *tagValues) {
    DbError err;
    log_->Info(boost::format("start to collect data ").str());

    ReadHiDataRequest req;
    req.stTime = start;
    req.enTime = end;
    req.reqType = 0;
    req.tPeriod = 0;
    strcpy(req.pointName, tag_name.c_str());
    auto *tag = new TagData[count];
#ifdef WIN32
    err.err_code = m_GetRawDataByTagName(&req, tag, &count);
#else
    err.err_code = GetRawDataByTagName(&req, tag, &count);
#endif
    if (err.err_code != 0) {
        GetErr(&err);
        log_->Error((boost::format("get value err :%1%,%2%") % err.err_code % err.err_msg).str());
        delete[] tag;
        return {err.err_code, err.err_msg};
    } else {
        log_->Error((boost::format("get value success ")).str());
        for (int i = 0; i < count; i++) {
            tagValues->push_back(tag[i]);
        }
    }
    log_->Info((boost::format("get value size :%1%") % tagValues->size()).str());
    return {err.err_code, err.err_msg};
}


DbError
DbVs::TagValuesGet(ReadHiDataRequest req, long &count, std::vector<TagData> *tagValues) {
    DbError err;
    log_->Info(boost::format("start to collect data ").str());
    auto *tag = new TagData[count];
#ifdef WIN32
    err.err_code = m_GetRawDataByTagName(&req, tag, &count);
#else
    err.err_code = GetRawDataByTagName(&req, tag, &count);
#endif
    if (err.err_code != 0) {
        GetErr(&err);
        log_->Error((boost::format("get value err :%1%,%2%") % err.err_code % err.err_msg).str());
        delete[] tag;
        return {err.err_code, err.err_msg};
    } else {
        log_->Error((boost::format("get value success ")).str());
        for (int i = 0; i < count; i++) {
            tagValues->push_back(tag[i]);
        }
    }
    log_->Info((boost::format("get value size :%1%") % tagValues->size()).str());
    return {err.err_code, err.err_msg};
}

DbError DbVs::TagAvgValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kAvg, tagData);
#else
    err.err_code = GetSummary(tag_name.c_str(),start,end,kAvg,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagMinValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kMin, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kMin,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagMaxValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kMax, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kMax,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagTimeAvgValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kAvg, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kAvg,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagIntegralValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kIntegralValue, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kIntegralValue,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagSumValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kSumValue, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kSumValue,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagSubValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kSubValue, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kSubValue,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagStartValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kStartValue, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kStartValue,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagEndValue(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kEndValue, tagData);
#else

    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kEndValue,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagValidCount(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
    err.err_code = m_GetSummary(tag_name.c_str(), start, end, kCount, tagData);
#else
    std::cout << GetSummary <<std::endl;
    err.err_code = GetSummary(tag_name.c_str(),start,end,kCount,tagData);
#endif
    if (err.err_code != 0) {
        std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
    } else {
        std::cout << "查询数据成功" << std::endl;
    }
    std::cout << "结束" << std::endl;
    return err;
}

DbError DbVs::TagDescGet(const std::string &tag_name, long start, long end, TagData *tagData, int vType) {
    log_->Info((boost::format("tag_name:%1%,start:%2%,end:%3%,vType:%4%,tagData:%5%") % tag_name % start % end % vType %
                tagData).str());
    DbError err;
    log_->Info("start to collect desc ");
#ifdef WIN32
    //std::cout << m_GetSummary << std::endl;
//    tagData->value = 1;
//    tagData->status = 1;
//    tagData->time = 168956236;
//    err.err_code = m_GetSummaryFilterEx(tag_name.c_str(), start, end, vType, "",tagData);
    // err.err_code = m_GetSummaryFilter(tag_name.c_str(), start, end, vType, "", -99999, 99999, 1, tagData);
#else
    //char *str = "";
        tagData->value = 1;
        tagData->status = 1;
        tagData->time = 168956236;
    //err.err_code = GetSummaryFilterEX(tag_name.c_str(),start,end,vType,str,tagData);
#endif
    if (err.err_code != 0) {
        log_->Error((boost::format("GetSummary(tag_name.c_str(),start,end,vType,tagData) err %1%:%2% ") % err.err_code %
                     err.err_msg).str());
        return err;
    }
    log_->Info("over to collect desc ");
    return err;
}

DbError DbVs::HistoryTime(const std::string &tag_name, long time, TagData *tagData) {

    DbError err;
    try {
        std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
        err.err_code = m_GetHistoryDataByTime(tag_name.c_str(), time, tagData);
#else
        std::cout << GetHistoryDataByTime <<std::endl;
        err.err_code = GetHistoryDataByTime(tag_name.c_str(), time, tagData);
#endif
        if (err.err_code != 0) {
            std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
        } else {
            std::cout << "查询数据成功" << std::endl;
        }
        std::cout << "结束" << std::endl;

    } catch (...) {
        std::cout << "捕获异常" << std::endl;
    }
    return err;
}


DbError DbVs::HistoryTimeSpan(const std::string &tag_name, long start, long end, TagData *tagData) {
    DbError err;
    try {
        std::cout << "开始获取数据" << std::endl;
#ifdef WIN32
        err.err_code = m_GetHistoryDataByTimeSpan(tag_name.c_str(), start, end, tagData);
#else
        /*        std::cout << GetHistoryDataByTimeSpan <<std::endl;
                err.err_code = GetHistoryDataByTimeSpan(tag_name.c_str(), start,end, tagData);*/
#endif
        /*if (err.err_code != 0) {
            std::cout << "TagValuesGet 报错了" << err.err_code << std::endl;
        } else {
            std::cout << "查询数据成功" << std::endl;
        }*/
        std::cout << "结束" << std::endl;

    } catch (...) {
        std::cout << "捕获异常" << std::endl;
    }
    return err;
}

DbError DbVs::TagGetAggregation(const std::string &tag_name, long start, long end, int req_type, int t_period,
                                TagData *tagData) {
    DbError err;
    if (tag_name.empty() || start == 0 || end == 0 || start >= end || tagData == nullptr) {
        log_->Error("TagGetAggregation arg is not valid");
        return {-1, "TagGetAggregation arg is not valid"};
    }
    ReadHiDataRequest req;
    req.stTime = start;
    req.enTime = end;
    req.reqType = req_type;
    req.tPeriod = t_period;
    strcpy(req.pointName, tag_name.c_str());
#ifdef WIN32
    err.err_code = m_GetAggregationDataByTagName(&req, tagData);
#else
    err.err_code = GetAggregationDataByTagName(&req, tagData);
#endif
    if (err.err_code != 0) {
        GetErr(&err);
        return err;
    }
    return err;
}

DbError DbVs::TagSnapshotByName(ReadHiDataRequest *req, std::vector<TagData> *tagValues) {
    DbError err;
    log_->Info(boost::format("start to collect tagSnapshotByName ").str());
//    ReadHiDataRequest req;
//    req.stTime = start;
//    req.enTime = end;
//    req.reqType = 0;
//    req.tPeriod = 0;
//    strcpy(req.pointName, tag_name.c_str());
    if (req->enTime < req->stTime) {
        err.err_code = kArgBad;
        GetErr(&err);
        return err;
    }
    auto tmp_count = (req->enTime - req->stTime) / req->tPeriod + 1;
    auto *tag = new TagData[tmp_count];

#ifdef WIN32
    err.err_code = m_GetSnapshotDataByTagName(req, tag);
#else
    err.err_code = GetSnapshotDataByTagName(req, tagValues->data());
#endif
    if (err.err_code != 0) {
        GetErr(&err);
        log_->Error((boost::format("get value err :%1%,%2%") % err.err_code % err.err_msg).str());
        delete[] tag;
        return {err.err_code, err.err_msg};
    } else {
        log_->Error((boost::format("get value success ")).str());
        for (int i = 0; i < tmp_count; i++) {
            auto x = tag[i];
            tagValues->push_back(tag[i]);
        }
    }
    log_->Info((boost::format("get value size :%1%") % tagValues->size()).str());
    log_->Info((boost::format("over")).str());
    return {err.err_code, err.err_msg};
}

DbError DbVs::TagDataInsert(InsertData *data, int count) {
    DbError err;
//#ifdef WIN32
//    err.err_code = m_AppendRTTagDataByBatch(data, count);
//#else
//    err.err_code = m_AppendRTTagDataByBatch(data, count);
//#endif
//    if (err.err_code != 0) {
//        GetErr(&err);
//        return err;
//    }
    return err;
}

