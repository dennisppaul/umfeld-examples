cmake_minimum_required(VERSION 3.20)

project(capture)                                               # set application name
set(UMFELD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../umfeld") # set path to umfeld library

option(ENABLE_CAPTURE "Enable camera capture" ON)

# --------- no need to change anything below this line ---------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add sources

include_directories(".")
file(GLOB SOURCE_FILES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# add umfeld

add_subdirectory(${UMFELD_PATH} ${CMAKE_BINARY_DIR}/umfeld-lib-${PROJECT_NAME})
add_umfeld_libs()

# allow camera access on macOS ny embedding Info.plist

#if (APPLE)
#    # Specify the path to your Info.plist file
#    set(INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist")
#
#    # Ensure the Info.plist file exists
#    if (EXISTS "${INFO_PLIST}")
#        target_link_options(${PROJECT_NAME} PRIVATE "SHELL:-sectcreate __TEXT __info_plist ${INFO_PLIST}")
#    else ()
#        message(FATAL_ERROR "Info.plist not found at ${INFO_PLIST}")
#    endif ()
#endif ()
