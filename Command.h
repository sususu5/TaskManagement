#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>
#include <memory>

template <typename Derived>
class Command {
public:
    void execute(const std::string& args) {
        (static_cast<Derived*>(this))->executeImpl(args);
    }
};

#include "TaskManager.h"
#include "Logger.h"

class AddCommand : public Command<AddCommand> {
public:
    AddCommand(TaskManager& manager) : taskManager(manager) {}
    void executeImpl(const std::string& args) {
        size_t pos1 = args.find(',');
        size_t pos2 = args.find(',', pos1 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            Logger::getInstance().log("Invalid command format.");
            return;
        }
        std::string description = args.substr(0, pos1);
        int priority = std::stoi(args.substr(pos1 + 1, pos2 - pos1 - 1));
        std::string dueDate = args.substr(pos2 + 1);
        taskManager.addTask(description, priority, dueDate);
        std::cout << "Task added successfully." << std::endl;
    }

private:
    TaskManager& taskManager;
};

class DeleteCommand : public Command<DeleteCommand> {
public:
    DeleteCommand(TaskManager& manager) : taskManager(manager) {}
    void executeImpl(const std::string& args) {
        try {
            size_t pos;
            int id = std::stoi(args, &pos);
            if (pos != args.size()) {
                Logger::getInstance().log("Invalid command format.");
                return;
            }
            taskManager.deleteTask(id);
            std::cout << "Task deleted successfully." << std::endl;
        } catch (const std::invalid_argument& e) {
            Logger::getInstance().log("Invalid command format.");
            return;
        } catch (const std::out_of_range& e) {
            Logger::getInstance().log("Invalid command format.");
            return;
        }
    }

private:
    TaskManager& taskManager;
};

class ListCommand : public Command<ListCommand> {
public:
    ListCommand(TaskManager& manager) : taskManager(manager) {}
    void executeImpl(const std::string& args) {
        try {
            int sortOption = 0;
            size_t pos;
            sortOption = std::stoi(args, &pos);
            if (pos != args.size()) {
                Logger::getInstance().log("Invalid command format.");
                return;
            }
            std::cout << "Tasks:" << std::endl;
            taskManager.listTasks(sortOption);
        } catch (const std::invalid_argument& e) {
            Logger::getInstance().log("Invalid command format.");
            return;
        } catch (const std::out_of_range& e) {
            Logger::getInstance().log("Invalid command format.");
            return;
        }
    }

private:
    TaskManager& taskManager;
};

#endif // COMMAND_H