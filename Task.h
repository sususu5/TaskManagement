#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Task {
public:
    int id;
    std::string description;
    int priority;
    std::string dueDate;

    std::string toString() const {
        std::ostringstream oss;
        oss << "Id: " << id
        << ", Description: " << description
        << ", Priority: " << priority
        << ", Due Date: " << dueDate;
        return oss.str();
    }
};

#endif // TASK_H