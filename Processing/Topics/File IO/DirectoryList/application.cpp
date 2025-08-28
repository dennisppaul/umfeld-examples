/**
 * Listing files in directories and subdirectories
 * 
 * This example has three functions:
 * 1) List the names of files in a directory
 * 2) List the names along with metadata (size, lastModified)
 *    of files in a directory
 * 3) List the names along with metadata (size, lastModified)
 *    of files in a directory and all subdirectories (using recursion)
 */

#include "Umfeld.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "File.h"

using namespace umfeld;

//@diff(forward_declaration)
std::vector<std::string> listFileNames(const std::string& dir);
std::vector<File> listFiles(const std::string& dir);
std::vector<File> listFilesRecursive(const std::string& dir);
void recurseDir(std::vector<File>& a, const std::string& dir);
std::string formatTimestamp(long long millisSinceEpoch);

void settings() {
    size(640, 360);
}

void setup() {

    // Using just the path of this sketch to demonstrate,
    // but you can list any directory you like.
    std::string path = sketchPath();

    println("Listing all filenames in a directory: ");
    std::vector<std::string> filenames = listFileNames(path); //@diff(std::vector)
    printArray(filenames);

    println("\nListing info about all files in a directory: ");
    std::vector<File> files = listFiles(path); //@diff(std::vector)
    for (int i = 0; i < files.size(); i++) {
        File f = files[i];
        println("Name: ", f.getName());
        println("Is directory: ", f.isDirectory());
        println("Size: ", f.length());
        std::string lastModified = formatTimestamp(f.lastModified());
        println("Last Modified: ", lastModified);
        println("-----------------------");
    }

    println("\nListing info about all files in a directory and all subdirectories: ");
    std::vector<File> allFiles = listFilesRecursive(path);

    for (const File& f : allFiles) {
        println("Name: ", f.getName());
        println("Full path: ", f.getAbsolutePath());
        println("Is directory: ", f.isDirectory());
        println("Size: ", f.length());
        std::string lastModified = formatTimestamp(f.lastModified());
        println("Last Modified: ", lastModified);
        println("-----------------------");
    }

    noLoop();
}

// Nothing is drawn in this program and the draw() doesn't loop because
// of the noLoop() in setup()
void draw() {
}

// This function returns all the files in a directory as an array of Strings
std::vector<std::string> listFileNames(const std::string& dir) {
    File file(dir);
    if (file.isDirectory()) {
        return file.list();
    } else {
        // If it's not a directory
        return {};
    }
}

// This function returns all the files in a directory as an array of File objects
// This is useful if you want more info about the file
std::vector<File> listFiles(const std::string& dir) {
    File file(dir);
    if (file.isDirectory()) {
        return file.listFiles();
    } else {
        // If it's not a directory
        return {};
    }
}

// Function to get a list of all files in a directory and all subdirectories
std::vector<File> listFilesRecursive(const std::string& dir) {
    std::vector<File> fileList;
    recurseDir(fileList, dir);
    return fileList;
}

// Recursive function to traverse subdirectories
void recurseDir(std::vector<File>& a, const std::string& dir) {
    File file(dir);
    if (file.isDirectory()) {
        // If you want to include directories in the list
        a.push_back(file);
        std::vector<File> subfiles = file.listFiles();
        for (const auto& subfile : subfiles) {
            // Call this function on all files in this directory
            recurseDir(a, subfile.getAbsolutePath());
        }
    } else {
        a.push_back(file);
    }
}

// Function to format a timestamp in a human-readable way
std::string formatTimestamp(long long millisSinceEpoch) {
    auto timePoint  = std::chrono::system_clock::from_time_t(millisSinceEpoch / 1000);
    auto time_t_val = std::chrono::system_clock::to_time_t(timePoint);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t_val), "%a %b %d %H:%M:%S %Y");
    return ss.str();
}
