#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>
#include <memory>

// class CommandBase {
// public:
//     virtual void execute(const std::string& args) = 0;
// };

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
            std::cout << "Invalid command format. Please use add <description>,<priority>,<durDate>" << std::endl;
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
                std::cout << "Invalid command format. Please use delete <id>" << std::endl;
                return;
            }
            taskManager.deleteTask(id);
            std::cout << "Task deleted successfully." << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid command format. Please use delete <id>" << std::endl;
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
        int sortOption = 0;
        if (!args.empty()) {
            sortOption = std::stoi(args);
        }
        taskManager.listTasks(sortOption);
    }

private:
    TaskManager& taskManager;
};

class UpdateCommand : public Command<UpdateCommand> {
public:
    UpdateCommand(TaskManager& manager) : taskManager(manager) {}
    void executeImpl(const std::string& args) {
        try {
            size_t pos1 = args.find(',');
            size_t pos2 = args.find(',', pos1 + 1);
            size_t pos3 = args.find(',', pos2 + 1); 
            if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
                std::cout << "Invalid command format. Please use update <id>,<description>,<priority>,<dueDate>" << std::endl;
                return;
            }
            int id = std::stoi(args.substr(0, pos1));
            std::string description = args.substr(pos1 + 1, pos2 - pos1 - 1);
            int priority = std::stoi(args.substr(pos2 + 1, pos3 - pos2 - 1));
            std::string dueDate = args.substr(pos3 + 1);
            taskManager.updateTask(id, description, priority, dueDate);
            std::cout << "Task updated successfully." << std::endl;
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

class CommandWrapper {
    struct Concept {
        virtual void execute(const std::string& args) = 0;
    };

    template <typename T>
    struct Model : Concept {
        T command;
        Model(T&& cmd) : command(std::move(cmd)) {}
        void execute(const std::string& args) {
            command.execute(args);
        }
    };

public:
    template <typename T>
    CommandWrapper(T cmd);
    void execute(const std::string& args) {
        impl->execute(args);
    }

private:
    std::unique_ptr<Concept> impl;
};

#endif // COMMAND_H