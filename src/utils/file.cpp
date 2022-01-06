//
// Created by ct on 2021/11/2.
//
#include "utils/flie.h"

int FileUtil::FileWrite(std::string path, std::string data, std::ios_base::openmode mode) {
    boost::filesystem::path filePath(path);
    if (!boost::filesystem::exists(filePath.parent_path().c_str())) {
        boost::filesystem::create_directories(filePath.parent_path().c_str());
    }

    std::ofstream f;
    f.open(path, mode);
    if (!f) {
        std::cout << "打开文件失败" << std::endl;
        return -1;
    }
    f << data << std::endl;
    f.close();
    return 0;
};

int FileUtil::FileReadAll(std::string path, std::string *data) {
    if (boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path)) {
        std::ifstream f(path);
        std::string data2((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        f.close();
        *data = data2;
        return 0;
    }
    return -1;
}

int FileUtil::FileReadLine(std::string path, std::vector<std::string> *data, int line) {
    if (boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path)) {
        std::ifstream f(path, std::ios::in);
        std::string tmp;
        for (int i = 0; i < line; i++) {
            if (!getline(f, tmp)) {
                f.close();
                return 0;
            }
            data->push_back(tmp);
        }
        return 0;
    }
    return -1;
}

int FileUtil::FileRename(std::string src, std::string dst) {
    boost::filesystem::path srcp(src);
    boost::filesystem::path dstp(dst);
    boost::filesystem::rename(srcp, dstp);
    //boost::filesystem::remove_all(srcp);
    return 0;
}
