#include "TaskManager.h"
#include "Logger.h"
#include <iostream>

TaskManager::TaskManager() : nextId(1) {
    loadTasks();
}

void TaskManager::addTask(const std::string& description, int priority, const std::string& dueDate) {
    Task task;
    task.id = nextId++;
    task.description = description;
    task.priority = priority;
    task.dueDate = dueDate;
    tasks.push_back(task);
    Logger::getInstance().log("Task added: " + task.toString());
    saveTasks();
}

void TaskManager::deleteTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    });
    if (it != tasks.end()) {
        Logger::getInstance().log("Task deleted: " + it->toString());
        tasks.erase(it);
        saveTasks();
    } else {
        std::cout << "Task not found." << std::endl;
    }
}

void TaskManager::updateTask(int id, const std::string& description, int priority, const std::string& dueDate) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    });
    if (it != tasks.end()) {
        it->description = description;
        it->priority = priority;
        it->dueDate = dueDate;
        Logger::getInstance().log("Task updated: " + it->toString());
        saveTasks();
    } else {
        std::cout << "Task not found." << std::endl;
    }
}

void TaskManager::saveTasks() const {
    std::ofstream outFile("tasks.txt");
    if (!outFile.is_open()) {
        Logger::getInstance().log("Failed to open task file for saving.");
        return;
    }

    for (const auto& task : tasks) {
        outFile << task.id << "," << task.description << "," << task.priority << "," << task.dueDate << std::endl;
    }
    outFile.close();
    Logger::getInstance().log("Tasks saved successfully.");
}

void TaskManager::listTasks(int sortOption) const {
    std::vector<Task> sortedTasks = tasks;
    switch (sortOption) {
        case 1:
            std::sort(sortedTasks.begin(), sortedTasks.end(), compareByPriority);
            break;
        case 2:
            std::sort(sortedTasks.begin(), sortedTasks.end(), compareByDueDate);
            break;
        default:
            break;
    }
    for (const auto& task : sortedTasks) {
        std::cout << task.toString() << std::endl;
    }
}

void TaskManager::loadTasks() {
    std::ifstream inFile("tasks.txt");
    if (!inFile.is_open()) {
        Logger::getInstance().log("Failed to open tasks file.");
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        Task task;
        char delimiter;
        iss >> task.id >> delimiter;
        std::getline(iss, task.description, ',');
        iss >> task.priority >> delimiter;
        iss >> task.dueDate;
        tasks.push_back(task);
        if (task.id >= nextId) {
            nextId = task.id + 1;
        }
    }
    inFile.close();
    Logger::getInstance().log("Tasks loaded successfully.");
}

bool TaskManager::compareByPriority(const Task& a, const Task& b) {
    return a.priority < b.priority;
}

bool TaskManager::compareByDueDate(const Task& a, const Task& b) {
    return a.dueDate < b.dueDate;
}