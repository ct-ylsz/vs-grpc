#pragma once
#include <iostream>
#include <boost/filesystem.hpp>

class FileUtil{
public:
    static int FileWrite(const std::string& path, const std::string& data, std::ios_base::openmode mode);
    static int FileReadAll(const std::string& path, std::string* data);
    static int FileReadLine(const std::string& path,std::vector<std::string>* data,int line);
    static int FileRename(std::string src, const std::string& dst);
};


