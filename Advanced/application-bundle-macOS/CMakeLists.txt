cmake_minimum_required(VERSION 3.12)

project(umfeld-application-bundle)                             # set application name
set(UMFELD_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../umfeld") # set path to umfeld library

# --------- no need to change anything below this line ---------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(".")
file(GLOB SOURCE_FILES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_subdirectory(${UMFELD_PATH} ${CMAKE_BINARY_DIR}/umfeld-lib-${PROJECT_NAME})
add_umfeld_libs()

# --------- make application bundle ----------------------------

# bundle assets // TODO move to 'data'
# install(FILES "${PROJECT_SOURCE_DIR}/RobotoMono-Regular.ttf" DESTINATION "../")   # include single resources files or ...
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION "../assets")              # ... entire directories

# bundle dynamic libraries
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Bundling dynamic libraries using dylibbundler..."
    COMMAND dylibbundler -od -b -x $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME} -d $<TARGET_FILE_DIR:${PROJECT_NAME}>/../libs/
    COMMENT ${CMAKE_COMMAND} -E echo "Dynamic libraries are bundled."
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/libs/ DESTINATION "../libs")

# configure cpack
set(CPACK_PACKAGE_NAME "Umfeld")
set(CPACK_PACKAGE_VENDOR "Dennis P Paul")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Umfeld is a C++ environment for audio and graphics based applications.")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_GENERATOR "Bundle")
set(CPACK_BUNDLE_NAME Umfeld)
set(CPACK_BUNDLE_ICON ${CMAKE_SOURCE_DIR}/Resources/Umfeld.icns)
set(CPACK_BUNDLE_PLIST ${CMAKE_SOURCE_DIR}/Resources/Info.plist)

set(CPACK_BUNDLE_STARTUP_COMMAND ${PROJECT_NAME})
include(CPack)

# run with `cmake -B build ; cmake --build build ; cd build ; cpack ; cd ..` from sketch folder
