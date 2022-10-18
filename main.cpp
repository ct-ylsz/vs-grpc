#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include "log/log.h"
#include "src/service/service.hpp"
#include "error/error.h"

ErrResp<int> Cmd(int argc, char *argv[], boost::program_options::variables_map *args) {
    boost::program_options::options_description des_cmd("\n Usage:Beat-Vs \n\n Options: \n");

    des_cmd.add_options()
            ("ip", boost::program_options::value<std::string>()->default_value("0.0.0.0"), "listen ip")
            ("port", boost::program_options::value<std::string>()->default_value("9485"), " port")
            ("path", boost::program_options::value<std::string>()->default_value("./"), "path")
            ("dll_path", boost::program_options::value<std::string>()->default_value("./"), "driver path")
            ("config_path", boost::program_options::value<std::string>()->default_value("./config.yml"), "config path")
            ("log_path", boost::program_options::value<std::string>()->default_value("./"), "config path")
            ("help", "help menu");
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, des_cmd), *args);
    }
    catch (...) {
        return {-1, "parse args failed"};
    }

    // 定义消息
    boost::program_options::notify(*args);

    if (args->empty()) {
        return {-2, "must pass valid args"};
    } else if (args->count("help")) {
        std::cout << des_cmd << std::endl;
        return {-3, "help option"};
    }

    return {};
}

int main(int argc, char **argv) {

    auto *log = new Logger;
    if (argc < 2) {
        log->Error("please input beat-vs run");
        return -1;
    }

    if (strcmp(argv[1], "run") != 0) {
        log->Error("please input beat-vs run ");
        return -2;
    }

    boost::program_options::variables_map args;
    auto err_resp = Cmd(argc, argv, &args);

    if (err_resp.err_code_ != 0) {
        log->Error((boost::format("%1%:%2%") % err_resp.err_code_ % err_resp.err_msg_).str());
        return err_resp.err_code_;
    }

    log->Info("server is starting ...");
    delete log;
    auto vs = VsServiceImpl::GetInstance();
    vs->ip_ = args["ip"].as<std::string>();
    vs->port_ = args["port"].as<std::string>();
    vs->config_path_ = args["config_path"].as<std::string>();
    vs->log_path_ = args["log_path"].as<std::string>();
    vs->Run();


    return 0;
}


//string GBK_2_UTF8(string gbkStr)
//{
//    string outUtf8 = "";
//    int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
//    WCHAR *str1 = new WCHAR[n];
//    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, str1, n);
//    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
//    char *str2 = new char[n];
//    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
//    outUtf8 = str2;
//    delete[]str1;
//    str1 = NULL;
//    delete[]str2;
//    str2 = NULL;
//    return outUtf8;
//}
//
//string UTF8_2_GBK(string utf8Str)
//{
//    string outGBK = "";
//    int n = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
//    WCHAR *str1 = new WCHAR[n];
//    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, str1, n);
//    n = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
//    char *str2 = new char[n];
//    WideCharToMultiByte(CP_ACP, 0, str1, -1, str2, n, NULL, NULL);
//    outGBK = str2;
//    delete[] str1;
//    str1 = NULL;
//    delete[] str2;
//    str2 = NULL;
//    return outGBK;
//}
//
//


//int main(int argc, char **argv) {
//    char dll_path[128];
//    char config_path[128];
//    strcpy(dll_path, "./");
//    strcpy(config_path, "./");
//
//    auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
//    if (err.err_code != 0) {
//        printf("%d", err.err_code);
//        return 1;
//    }
//
////    long count = 1;
////    auto *dataF = new TagDataF();
////    ReadHiDataRequest req;
////    strcpy(req.pointName, "d1");
////    req.stTime = 946656000;
////    req.enTime = 1666041499;
////    req.tPeriod = 0;
////    req.reqType = 0;
////    auto *data3 = new std::vector<TagData>();
////
////    err = DbVs::TagValuesGet("d1", req.stTime, req.enTime, count, data3);
////
////
////    auto *data2 = new std::vector<TagInfo>();
////    err = DbVs::TagListByCount(0, data2, count);
////    if (err.err_code != 0) {
////        printf("%d", err.err_code);
////        return 1;
////    }
////    std::vector<std::string> names;
////    for (int i = 0; i < count; i++) {
////        names.emplace_back(data2->data()->name);
////    }
////    while (true) {
////        auto *data = new std::vector<TagData>();
////        err = DbVs::GetRTDataByBatch(names, data);
////        delete data;
////    }
////
////
////    InsertData_struct x;
////    x.value = 1.11;
////    x.status = 1;
////    x.type = 1;
////    x.time = 1662273447;
////    strcpy(x.pointName, "111");
////    err = DbVs::TagDataInsert(&x, 1);
////    if (err.err_code != 0) {
////        DbVs::DbReleaseConnect();
////        printf("%d", err.err_code);
////        return 2;
////    }
////    long count = 1024;
////    ReadHiDataRequest req;
////    strcpy(req.pointName, "d5");
////    req.stTime = 1538323200;
////    req.enTime = 1541001600;
////    long tmp_count = 0;
////    while (count == 1024 && req.stTime < req.enTime) {
////        auto *data2 = new std::vector<TagData>();
////        err = DbVs::TagValuesGet(req, count, data2);
////        if (err.err_code != 0) {
////            break;
////        }
////        if (!data2->empty()) {
////            tmp_count += count; //总数量
////            req.stTime = data2->back().time + 1;
////            delete data2;
////        } else {
////            tmp_count += count;
////            delete data2;
////        }
////    }
////    std::cout << tmp_count;
//
//    // auto count = 1501603199 - 1498838400 + 1;
//
//    auto *data = (InsertData_struct *) malloc(sizeof(InsertData_struct) * 1);
//    for (int i = 0; i < 1; i++) {
//        for (int j = 0; j < 1; j++) {
//            data[j].value = 2.0;
//            data[j].type = 0;
//            strcpy(data[j].pointName, "dd2");
//            data[j].status = 2;
//            data[j].time = 1501603198 + j;
//        }
//        err = DbVs::TagDataInsert(data, 1);
//        if (err.err_code != 0) {
//            printf("%d", err.err_code);
//            free(data);
//            return 2;
//        }
//    }
//    std::cout << "write data success" << std::endl;
//    free(data);
//    return 0;
//}


//int main(int argc, char **argv) {
//    auto *log = new Logger;
//    char *dll_path = (char *) malloc(128);
//    char *config_path = (char *) malloc(128);
//
//    strcpy(dll_path, "./");
//    strcpy(config_path, "./");
//    auto err = DbVs::DbConnect(dll_path, config_path, nullptr, nullptr);
//    free(dll_path);
//    free(config_path);
//
//    if (err.err_code != 0) {
//        DbVs::DbReleaseConnect();
//        log->Error((boost::format("connect database failed :%1%:%2%") % err.err_code % err.err_msg).str());
//        return err.err_code;
//    }
//    ReadHiDataRequest req;
//    strcpy(req.pointName,"test_001");
//    req.tPeriod = 0;
//    req.stTime = 948424025;
//    req.enTime = 1642734451;
//    auto *tagValues = new std::vector<TagData>();
//    long count = 1;
//    err = DbVs::TagValuesGet(req,count, tagValues);
//    if (err.err_code != 0){
//        std::cout << err.err_code << "---" << err.err_msg << std::endl;
//        return -1;
//    }
////    InsertData d;
////    time_t t;
////    time(&t);
////    d.time = t;
////    strcpy(d.pointName,"test_001");
////    d.type = 1;
////    d.value = 123456;
////    d.status = 100;
////    std::cout << "ts" << t <<std::endl;
////    err = DbVs::TagDataInsert(&d);
////    if (err.err_code != 0){
////        std::cout << err.err_code << "---" << err.err_msg << std::endl;
////        return -1;
////    }
//
//    DbVs::DbReleaseConnect();
//    return 0;
//}

