#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <ctime>
#include "Umfeld.h"

/**
   * simple File class for the example directory_list
   * provides file and directory operations using std::filesystem(C++17)
   */
class File {
private:
    std::filesystem::path path_;

public:
    // Constructor
    explicit File(const std::string& pathname) : path_(pathname) {}

    // Copy constructor
    File(const File& other) : path_(other.path_) {}

    // Assignment operator
    File& operator=(const File& other) {
        if (this != &other) {
            path_ = other.path_;
        }
        return *this;
    }

    // Get filename (equivalent to Java getName())
    std::string getName() const {
        return path_.filename().string();
    }

    // Get absolute path (equivalent to Java getAbsolutePath())
    std::string getAbsolutePath() const {
        std::error_code ec;
        auto            abs_path = std::filesystem::absolute(path_, ec);
        return ec ? path_.string() : abs_path.string();
    }

    // Check if this is a directory (equivalent to Java isDirectory())
    bool isDirectory() const {
        std::error_code ec;
        return std::filesystem::is_directory(path_, ec);
    }

    // Check if this is a regular file
    bool isFile() const {
        std::error_code ec;
        return std::filesystem::is_regular_file(path_, ec);
    }

    // Check if file/directory exists
    bool exists() const {
        std::error_code ec;
        return std::filesystem::exists(path_, ec);
    }

    // Get file size in bytes (equivalent to Java length())
    size_t length() const {
        std::error_code ec;
        if (isFile()) {
            return std::filesystem::file_size(path_, ec);
        }
        return 0;
    }

    // Get last modified time as milliseconds since epoch (equivalent to Java lastModified())
    long long lastModified() const {
        std::error_code ec;
        auto            ftime = std::filesystem::last_write_time(path_, ec);
        if (ec) {
            return 0;
        }

        // Convert to system clock time
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());

        // Convert to milliseconds since epoch
        return std::chrono::duration_cast<std::chrono::milliseconds>(sctp.time_since_epoch()).count();
    }

    // List directory contents as filenames (equivalent to Java list())
    std::vector<std::string> list() const {
        std::vector<std::string> result;
        if (!isDirectory()) {
            return result;
        }

        std::error_code ec;
        for (const auto& entry: std::filesystem::directory_iterator(path_, ec)) {
            if (!ec) {
                result.push_back(entry.path().filename().string());
            }
        }
        return result;
    }

    // List directory contents as File objects (equivalent to Java listFiles())
    std::vector<File> listFiles() const {
        std::vector<File> result;
        if (!isDirectory()) {
            return result;
        }

        std::error_code ec;
        for (const auto& entry: std::filesystem::directory_iterator(path_, ec)) {
            if (!ec) {
                result.emplace_back(entry.path().string());
            }
        }
        return result;
    }

    // Get the path as string
    std::string getPath() const {
        return path_.string();
    }

    // Get parent directory
    File getParent() const {
        return File(path_.parent_path().string());
    }
};