//
// Created by ct on 2021/11/10.
//

#ifndef HIBEAT_CONFIG_H
#define HIBEAT_CONFIG_H


#include <iostream>
#include <string>
#include "resclass/sourceinfo.h"

const std::string ConfigKeyDbIp = "VESTORE.SERVER NAME";
const std::string ConfigKeyDbPort = "VESTORE.SERVER PORT";
const std::string ConfigKeyDbSite = "VESTORE.SITE NAME";
const std::string ConfigKeyDbType = "CONFIG.SERV TYPE";
const std::string ConfigKeyDbWrite = "CONFIG.WRITE WAY";
const std::string ConfigKeyDbLog = "CONFIG.LOG SWITCH";

class Config {
public:
    std::string ip_;
    std::string port_;
    std::string config_path_;

};

void ParseYamlFile(const std::string &config_path, SourceInfo *s);

void ParseYamlConfig(const std::string &config_path, Config *s);


#endif //HIBEAT_CONFIG_H
