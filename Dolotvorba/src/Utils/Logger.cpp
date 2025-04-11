#include "Logger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

const std::string Logger::log_directory = "logs/";
const std::string Logger::latest_log_file = "latest.log";

void Logger::initialize_logger() {
    std::filesystem::create_directory(log_directory);

    cleanup_old_logs();

    std::string latest_log_path = log_directory + latest_log_file;
    if (std::filesystem::exists(latest_log_path)) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm time_info;
        localtime_s(&time_info, &in_time_t);
        std::stringstream ss;
        ss << std::put_time(&time_info, "%Y-%m-%d %H-%M-%S");
        std::string current_time = ss.str();

        std::string new_log_name = log_directory + "Log_" + current_time + ".log";
        std::filesystem::rename(latest_log_path, new_log_name);
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm time_info;
    localtime_s(&time_info, &in_time_t);
    std::stringstream ss;
    ss << std::put_time(&time_info, "%d/%m/%Y %H:%M:%S");
    std::string current_time = ss.str();

    std::string log_message = "[" + log_level_to_string(level) + "] (" + current_time + ") - " + message;

    std::cout << log_message << std::endl;

    write_log(log_message);
}

void Logger::cleanup_old_logs() {
    auto now = std::chrono::system_clock::now();
    auto cutoff_time = now - std::chrono::hours(24 * 14);

    for (const auto& entry : std::filesystem::directory_iterator(log_directory)) {
        if (entry.is_regular_file()) {
            auto file_time = std::filesystem::last_write_time(entry);
            auto file_time_point = std::chrono::time_point_cast<std::chrono::system_clock::time_point::duration>(file_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
            if (file_time_point < cutoff_time) {
                std::filesystem::remove(entry);
            }
        }
    }
}

std::string Logger::log_level_to_string(LogLevel level) {
    switch (level) {
    case INFO: return "INFO";
    case WARNING: return "WARNING";
    case ERROR: return "ERROR";
    case DEBUG: return "DEBUG";
    default: return "UNKNOWN";
    }
}

void Logger::write_log(const std::string& log_message) {
    std::ofstream log_file;
    log_file.open(log_directory + latest_log_file, std::ios_base::app);
    if (log_file.is_open()) {
        log_file << log_message << std::endl;
    }
    else {
        std::cerr << "Unable to open log file: " << log_directory + latest_log_file << std::endl;
    }
    log_file.close();
}