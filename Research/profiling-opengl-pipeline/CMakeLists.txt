cmake_minimum_required(VERSION 3.12)

project(profiling-opengl-pipeline)                             # set application name
set(UMFELD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../umfeld") # set path to umfeld library
#set(UMFELD_OPENGL_VERSION "OPENGL_3_3_CORE")
set(UMFELD_OPENGL_VERSION "OPENGL_ES_3_0")
set(ENABLE_ANGLE ON)

# --------- no need to change anything below this line ------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(".")
file(GLOB SOURCE_FILES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(${UMFELD_PATH} ${CMAKE_BINARY_DIR}/umfeld-lib-${PROJECT_NAME})
add_umfeld_libs()

