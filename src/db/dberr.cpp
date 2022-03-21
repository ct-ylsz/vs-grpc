//
// Created by ct on 2021/11/25.
//
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "db/dberr.h"


std::string DbError::ToString() const {
    rapidjson::StringBuffer strBuf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> write(strBuf);
    write.StartObject();
    write.Key("err_code");
    write.Int(err_code_);
    write.Key("err_msg");
    write.String(err_msg_.c_str());
    write.EndObject();
    return strBuf.GetString();
}
