# Cmake version 3.0 or newer required
cmake_minimum_required(VERSION 3.0)

# Create compile command json file for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(L-SystemInterpreter
    VERSION 1.0
    LANGUAGES CXX
    DESCRIPTION "L-System implementation for C++ project")

# Include src/l-SystemInterpreter
add_subdirectory(source/l-SystemInterpreter)

# Include test/l-SystemInterpreterTest
add_subdirectory(test/l-SystemInterpreterTest)
