#pragma once

#include <fstream>
#include <string>

class Logger {
public:
    Logger(Logger const &) = delete;
    Logger(Logger &&) = delete;
    void operator=(Logger const &) = delete;
    Logger &operator=(Logger &&) = delete;
    static Logger &getInstance();
    void log(const std::string &message);
    void setPath(const std::string &path);

private:
    Logger();
    ~Logger();

    // Open the log file if not already open
    void openLogFile();

    std::string path;
    std::ofstream logFile; // Log file stream
    std::string getCurrentTime() const;
};
