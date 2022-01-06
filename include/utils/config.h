//
// Created by ct on 2021/11/10.
//

#ifndef HIBEAT_CONFIG_H
#define HIBEAT_CONFIG_H


#include <iostream>
#include <string>
#include "resclass/sourceinfo.h"
#include "resclass/pi_config.h"
void ParseYamlFile(const std::string& config_path,SourceInfo *s);

void ParseYamlConfig(const std::string& config_path,PiConfig *s);



#endif //HIBEAT_CONFIG_H
