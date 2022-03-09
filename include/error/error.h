//
// Created by ct on 2021/10/31.
//

#ifndef HIBEAT_ERROR_H
#define HIBEAT_ERROR_H

#include <string>
#include <iostream>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "error/error.h"
template<class T>
class ErrResp {
public:
    int err_code_ = 0;
    std::string err_msg_;
    T data_;
public:
    ErrResp() {
        err_code_ = 0;
        err_msg_ = "ok";
    }

    ErrResp(int err_code, std::string err_msg) :
            err_code_(err_code), err_msg_(err_msg) {
    }

    ErrResp(int err_code, std::string err_msg, T data) :
            err_code_(err_code), err_msg_(err_msg), data_(data) {
    }

    std::string ToString() {
        rapidjson::StringBuffer str_buf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
        write.StartObject();
        write.Key("code");
        write.Int(err_code_);
        write.Key("msg");
        write.String(err_msg_.c_str());
        write.Key("data");
        data_.ToJsonString(&write);
        write.EndObject();
        return str_buf.GetString();
    }
};


#endif //HIBEAT_ERROR_H
