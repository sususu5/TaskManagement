#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Task.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

class TaskManager {
public:
    TaskManager();
    void addTask(const std::string& description, int priority, const std::string& dueDate);
    void deleteTask(int id);
    void updateTask(int id, const std::string& description, int priority, const std::string& dueDate);
    // 0: according to Id, 1: according to priority, 2: according to due date
    void listTasks(int sortOption = 0) const;
    void loadTasks();
    void saveTasks() const;

private:
    std::vector<Task> tasks;
    int nextId;
    static bool compareByPriority(const Task& a, const Task& b);
    static bool compareByDueDate(const Task& a, const Task& b);
};


#endif // TASK_MANAGER_H