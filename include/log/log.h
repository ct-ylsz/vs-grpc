//
// Created by ct on 2021/10/31.
//

#ifndef HIBEAT_LOG_H
#define HIBEAT_LOG_H

#pragma once

#include <iostream>
#include <boost/log/expressions.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <ctime>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <mutex>

namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace trvl = boost::log::trivial;

class Logger {
public:
    static inline std::once_flag once_ = std::once_flag();
public:
    Logger() {
        std::call_once(once_, []() {
            if (!boost::filesystem::exists("./log/")) {
                boost::filesystem::create_directory("./log/");
            }
            auto consoleSink = boost::log::add_console_log
                    (
                            std::cout,
                            keywords::format = "[%TimeStamp%]: %Message%",
                            keywords::auto_flush = true
                    );
            consoleSink->set_filter(
                    trvl::severity >= trvl::debug
            );
            auto sink = boost::log::add_file_log
                    (
                            keywords::open_mode = std::ios::out | std::ios::app,
                            keywords::file_name = "./log/beat_%N.log",                                        /*< file name pattern >*/
                            keywords::target_file_name = "beat_%Y%m%d_%N.log",
                            keywords::rotation_size =
                                    10 * 1024 *
                                    1024,                                   /*< rotate files every 10 MiB... >*/
                            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0,
                                                                                                0), /*< ...or at midnight >*/
                            keywords::format = "[%TimeStamp%]: %Message%",                                 /*< log record format >*/
                            keywords::auto_flush = true
                    );
            sink->locked_backend()->set_file_collector(sinks::file::make_collector(
                    keywords::target = "./log/",                         // 备份日志文件保存目录
                    keywords::max_size = 10 * 1024 * 1024 * 10  //所有日志加起来的最大大小
            ));
            boost::log::add_common_attributes();
        });
        slog_ = new boost::log::sources::severity_logger<boost::log::trivial::severity_level>();
    }

    void Info(const std::string &log) {
        BOOST_LOG_SEV(*slog_, boost::log::trivial::info) << log.c_str();
    }

    void Warn(const std::string &log) {
        BOOST_LOG_SEV(*slog_, boost::log::trivial::warning) << log.c_str();
    }

    void Debug(const std::string &log) {
        BOOST_LOG_SEV(*slog_, boost::log::trivial::debug) << log.c_str();
    }

    void Error(const std::string &log) {
        BOOST_LOG_SEV(*slog_, boost::log::trivial::error) << log.c_str();
    }

private:
    boost::log::sources::severity_logger<boost::log::trivial::severity_level> *slog_;
};

#endif