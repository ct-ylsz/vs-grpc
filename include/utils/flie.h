#pragma once
#include <iostream>
#include <boost/filesystem.hpp>

class FileUtil{
public:
    static int FileWrite(std::string path, std::string data, std::ios_base::openmode mode);
    static int FileReadAll(std::string path, std::string* data);
    static int FileReadLine(std::string path,std::vector<std::string>* data,int line);
    static int FileRename(std::string src, std::string dst);
};


