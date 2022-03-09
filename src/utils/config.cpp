//
// Created by ct on 2021/11/10.
//

#include "utils/config.h"
#include "yaml-cpp/yaml.h"
#include <string>
#include <iostream>
#include "resclass/sourceinfo.h"

void ParseYamlFile(const std::string &config_path, SourceInfo *s) {
    YAML::Node config;
    // 当文件不存在或yaml格式出错时，抛异常
    try {
        config = YAML::LoadFile(config_path);
    } catch (...) {
        printf("error loading file, yaml file error or not exist.\n");
        return;
    }
    std::cout << config["source"].Type() << std::endl;
/*
    //读取不存在的node值，报YAML::TypedBadConversion异常
    try{
        auto source = config["source"].as<std::map<>>();
    }catch(YAML::TypedBadConversion<YAML::NodeType::Null> &e){
        std::cout<<"source node is NULL"<<std::endl;
    }//TypedBadConversion是模板类，读取什么类型的参数就传入什么类型
*/

    s->username_ = config["source"]["username"].as<std::string>();
    s->password_ = config["source"]["password"].as<std::string>();
    s->addr_ = config["source"]["addr"].as<std::string>();

}


void ParseYamlConfig(const std::string &config_path, Config *s) {
    YAML::Node config;
    // 当文件不存在或yaml格式出错时，抛异常
    try {
        config = YAML::LoadFile(config_path);
    } catch (...) {
        printf("error loading file, yaml file error or not exist.\n");
        return;
    }
    if (config["config"].Type() == YAML::NodeType::Undefined) {
        printf("config not exist.\n");
        return;
    }
    s->ip_ = config["config"]["ip"].as<std::string>();
    s->port_ = config["config"]["port"].as<std::string>();
}
