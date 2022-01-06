#include <memory>
#include <string>
#include <iostream>
#include <grpc++/grpc++.h>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include "log/log.h"
#include "error/error.h"
#include "src/service/service.hpp"

ErrResp<int> Cmd(int argc, char *argv[], boost::program_options::variables_map *args) {
    boost::program_options::options_description des_cmd("\n Usage:HiBeatC \n\n Options: \n");

    des_cmd.add_options()
            ("ip", boost::program_options::value<std::string>()->default_value("0.0.0.0"), "listen ip")
            ("port", boost::program_options::value<std::string>()->default_value("9485"), "port")
            ("type", boost::program_options::value<std::string>()->default_value("1"), "type")
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

//#include "db/dbvs.h"
//#include "iostream"
//
//int main(int argc, char **argv) {
//    auto err = DbVs::DbConnect("./", "./", nullptr, nullptr);
//    if (err.err_code != 0) {
//        std::cout << "DbConnect  " << err.err_code << "  " << err.err_msg << std::endl;
//        return -1;
//    }
//    auto *tagValues = new std::vector<TagData>();
//    ReadHiDataRequest req;
//    req.stTime = 1638685047;
//    req.enTime = 1639117047;
//    req.tPeriod = 1000;//(1638835047 - 1638865047) 1638841047 1638851047 1638856047 1638858047
//    req.reqType = 0;
//    strcpy(req.pointName, "test_001");
//    long count = 1000;
//    err = DbVs::TagValuesGet(req, count, tagValues);
//    if (err.err_code != 0) {
//        std::cout << "TagValuesGet" << err.err_code << err.err_msg << std::endl;
//        return -2;
//    }
//    tagValues->clear();
//    delete tagValues;
//    long start = 1638685047;
//    long end = 1639117047;
//    TagData data;
//    err = DbVs::TagDescGet("test_001", start, end, &data, 1);
//    if (err.err_code != 0) {
//        std::cout << "TagDescGet" << err.err_code << err.err_msg << std::endl;
//        return -2;
//    }
//    err = DbVs::TagValidCount("test_001", start, end, &data);
//    if (err.err_code != 0) {
//        std::cout << "TagValidCount" << err.err_code << err.err_msg << std::endl;
//        return -2;
//    }
//
//
//    err = DbVs::TagGetAggregation("dec01-test_001", start, end, 1, 0, &data);
//    if (err.err_code != 0) {
//        std::cout << "TagGetAggregation" << err.err_code << err.err_msg << std::endl;
//        return -2;
//    }
//
//    err = DbVs::DbReleaseConnect();
//    if (err.err_code != 0) {
//        std::cout << "DbReleaseConnect  " << err.err_code << err.err_msg << std::endl;
//        return -2;
//    }
//    return 0;
//}

int main(int argc, char **argv) {

    auto *log = new Logger;
    if (argc < 2) {
        log->Error("please input beat-pi run");
        return -1;
    }

    if (strcmp(argv[1], "run") != 0) {
        log->Error("please input beat-pi run ");
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

