//
// Created by ct on 2021/10/31.
//

#ifndef HIBEAT_REQUEST_H
#define HIBEAT_REQUEST_H

#pragma once

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "error/error.h"
#include "sourceinfo.h"
#include "arrange_info.h"
#include "block.h"
#include "task.h"
#include "tasks.h"
#include "time_section.h"
#include "kv.h"
#include "blockInfo.h"
#include "range.h"
#include "tag.h"
#include "path.h"

class RequestPing : public Path, public Kvs {
};

class RequestTagInfo : public Path, public Tag {
public:
    void ToObj(const std::string &data);
};

class RequestTagData : public Path, public Tag, public TimeSection {
public:
    void ToObj(const std::string &data);
};

class RequestTagList : public SourceInfo, public Kvs {
public:
    long page_ = 0;
    long size_ = 0;
public:
    void ToObj(const std::string &data);
};

class RequestMetaData {
public:
    std::string path_;
public:
    ErrResp<int> ToObj(std::string data) {
        return {0, "ok"};
    }
};

class RequestDesc : public TimeSection {
public:
    ArrangeInfo arrange_;
public:
    void ToObj(const std::string &data);
};

class RequestCollectData {
public:
    Tasks tasks_;
public:
    void ToObj(const std::string &data);
};


class RequestTimeSection : public Path {
public:
    Tag tag_;
public:
    void ToObj(const std::string &data);
};

class RequestGetHierarchical : public Kvs, public Path {
public:
    void ToObj(const std::string &data);
};

class RequestTagDataGet : public Kvs, public BlockInfo, public Path {
public:
    int page_;
    int size_;
public:
    void ToObj(const std::string &data);
};

class RequestGetEigenvalue : public Kvs, public Path {
public:
    Range range_;
    TagInfoInternal tag_info_;
    std::string order_;
    std::vector<std::string> verifies_;

public:
    void ToObj(const std::string &data);
};

class RequestGetEigenvalueByBlock : public Kvs, public Path {
public:
    BlockInfo block_info_;
public:
    void ToObj(const std::string &data);
};


class RequestDoTask : public Kvs {
public:
    std::string action_;
    std::string container_id_;
    std::string event_log_path_;
    std::string event_id_;
    std::string container_uid_;
    std::string batch_id_;
    std::vector<BlockMap> block_;
public:
    void ToObj(const std::string &data);
};


class RequestGetNextBlockReq : public Path, public Kvs {
public:
    TagInfoInternal tag_info_;
    int64_t start_ = 0;
    int64_t end_ = 0;
    std::string order_;
    int64_t shard_size_;
    std::vector<std::string> select_fields_;
    std::vector<std::string> verifies_;
public:
    void ToObj(const std::string &data);
};

class RequestConfigSet : public Path {
public:
    std::map<std::string, std::string> kvs_;
public:
    void ToObj(const std::string &data);
};


#endif //HIBEAT_REQUEST_H
