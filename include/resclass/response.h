//
// Created by ct on 2021/10/31.
//

#ifndef HIBEAT_RESPONSE_H
#define HIBEAT_RESPONSE_H

#pragma once

#include <string>
#include <utility>
#include <ctime>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

enum ResponseErrors {
    kResponseOK = 10000,
    kErrorBadRequest,
    kErrorInternal = 90000,
};

template<class T>
class ResponseHttp {
public:
    int code_ = kResponseOK;
    std::string message_ = "success";
    int64_t timestamp_ = 0;
    T data;
public:
    std::string ToString() {
        rapidjson::StringBuffer str_buf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
        time_t t;
        time(&t);
        write.StartObject();
        write.Key("code");
        write.Int(code_);
        write.Key("message");
        write.String(message_.c_str());
        write.Key("timestamp");
        write.Int64(t);
        write.EndObject();
        return str_buf.GetString();
    }

    std::string ToErrString(int code, std::string msg) {
        time_t t;
        time(&t);
        code_ = code;
        message_ = std::move(msg);
        rapidjson::StringBuffer str_buf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
        write.StartObject();
        write.Key("code");
        write.Int(code_);
        write.Key("message");
        write.String(message_.c_str());
        write.Key("timestamp");
        write.Int64(t);
        write.EndObject();
        return str_buf.GetString();
    }


    std::string ToJsonString() {
        time_t t;
        time(&t);
        rapidjson::StringBuffer str_buf;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> write(str_buf);
        write.StartObject();
        write.Key("code");
        write.Int(code_);
        write.Key("message");
        write.String(message_.c_str());
        write.Key("timestamp");
        write.Int64(t);
        write.Key("data");
        data.ToJsonString(&write);
        write.EndObject();
        return str_buf.GetString();
    }
};


#endif //HIBEAT_RESPONSE_H
