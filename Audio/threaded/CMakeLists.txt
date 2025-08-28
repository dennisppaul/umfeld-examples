cmake_minimum_required(VERSION 3.12)

<<<<<<<< HEAD:Audio/threaded/CMakeLists.txt
project(threaded)                                              # set application name
set(UMFELD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../umfeld") # set path to umfeld library
========
project(array_2d)                                 # set application name
set(UMFELD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../umfeld") # set path to umfeld library
>>>>>>>> 89ad73b (add: processing examples):Processing/Basics/Arrays/array_2d/CMakeLists.txt

# --------- no need to change anything below this line ------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(".")
file(GLOB SOURCE_FILES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(${UMFELD_PATH} ${CMAKE_BINARY_DIR}/umfeld-lib-${PROJECT_NAME})
add_umfeld_libs()
