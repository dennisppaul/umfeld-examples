cmake_minimum_required(VERSION 3.12)

project(drawing-in-mouse-pressed)                                               # set application name
set(UMFELD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../umfeld")                  # set path to umfeld library

# --------- no need to change anything below this line ------------

set(CMAKE_CXX_STANDARD 17)                                                      # set c++ standard, this needs to happen before `add_executable`
set(CMAKE_CXX_STANDARD_REQUIRED ON)                                             # minimum is C++17 but 20 and 23 should also be fine

include_directories(".")                                                        # add all `.h` header files from this directory
file(GLOB SOURCE_FILES "*.cpp")                                                 # collect all `.cpp` source files from this directory
add_executable(${PROJECT_NAME} ${SOURCE_FILES})                                 # add source files to application

#set(UMFELD_OPENGL_VERSION "OPENGL_3_3_CORE")                                   # set OpenGL version. currently available: "OPENGL_2_0", "OPENGL_3_3_CORE" or "OPENGL_ES_3_0"
add_subdirectory(${UMFELD_PATH} ${CMAKE_BINARY_DIR}/umfeld-lib-${PROJECT_NAME}) # add umfeld location
add_umfeld_libs()                                                               # add umfeld library
