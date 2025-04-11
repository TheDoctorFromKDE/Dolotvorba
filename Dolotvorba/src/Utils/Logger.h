#pragma once

#include <string>

enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
public:
    static void initialize_logger();
    static void log(LogLevel level, const std::string& message);
    static void cleanup_old_logs();

private:
    static std::string log_level_to_string(LogLevel level);
    static void write_log(const std::string& log_message);
    static const std::string log_directory;
    static const std::string latest_log_file;
};