cmake_minimum_required(VERSION 3.5)

project(macro_string)

# The version number
set(test_VERSION_MAJOR 1)
set(test_VERSION_MINOR 0)
#set(test_VERSION_STR "\"demo11_str.h\"")
set(test_VERSION_STR demo11_str)

# configure a header file to pass some of the CMake settings to
# source code(demo11Config.h.in), the file demoConfig.h does't exists 
configure_file(
        "${PROJECT_SOURCE_DIR}/macroConfig.h.in"
        "${PROJECT_BINARY_DIR}/macroConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find demoConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the exectuable
add_executable(macro_test main.cpp)

