#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <mutex>
#include <fstream>

class Logger {
public:
    static Logger& getInstance();

    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(const std::string& message);
    ~Logger();

private:
    Logger();
    std::ofstream logFile;
    std::mutex mutex;
};

#endif // LOGGER_H
