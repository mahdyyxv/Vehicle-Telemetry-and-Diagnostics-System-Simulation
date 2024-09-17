#include "Logger.hpp"
#include <ctime>
#include <iostream>
#include <stdexcept>

Logger &Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setPath(const std::string &path) {
    this->path = path;
}

Logger::Logger() {}

Logger::~Logger() {
    try {
        if (logFile.is_open()) {
            logFile.close();
            if (logFile.fail()) {
                throw std::ios_base::failure("Failed to close log file properly");
            }
        }
    } catch (const std::ios_base::failure &e) {
        std::cerr << "Error in Logger destructor: " << e.what() << std::endl;
    }
}

void Logger::log(const std::string &message) {

    // Ensure the log file is open
    if (!logFile.is_open()) {
        openLogFile();
    }

    try {
        if (!logFile.is_open()) {
            throw std::ios_base::failure("Log file is not open");
        }
        logFile << getCurrentTime() << " : " << message << std::endl;
        if (logFile.fail()) {
            throw std::ios_base::failure("Failed to write to log file");
        }
    } catch (const std::exception &e) {
        std::cerr << "Error in Logger::log: " << e.what() << std::endl;
    }
}

void Logger::openLogFile() {
    try {
        if (path.empty()) {
            throw std::ios_base::failure("Log file path is not set");
        }
        logFile.open(path, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::ios_base::failure("Failed to open log file at: " + path);
        }
    } catch (const std::ios_base::failure &e) {
        std::cerr << "Error in Logger::openLogFile: " << e.what() << std::endl;
    }
}

std::string Logger::getCurrentTime() const {
    std::time_t now = std::time(nullptr);
    struct tm *local_time = std::localtime(&now);

    char date_time[100];
    if (std::strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S",
                      local_time) == 0) {
        throw std::runtime_error("Failed to format date and time");
    }
    return date_time;
}
