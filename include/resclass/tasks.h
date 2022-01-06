//
// Created by ct on 2021/11/3.
//

#ifndef HIBEAT_TASKS_H
#define HIBEAT_TASKS_H
class Task{
public:
    ArrangeInfo source_info_;
    std::string status_file_path_ = "";
    std::string task_schedule_file_path_ = "";
    Block eigenvalue_;
    TaskPath task_path_;
};


class Tasks{
public:
    std::vector<Task> inline_tasks_;
};


#endif //HIBEAT_TASKS_H
