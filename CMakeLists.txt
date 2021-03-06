# Cmake version 3.0 or newer required
cmake_minimum_required(VERSION 3.0)

# Create compile command json file for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(L-SystemInterpreter
    VERSION 1.0
    LANGUAGES CXX
    DESCRIPTION "L-System implementation for C++ project")

########################################
## Variables
########################################

# Output directory
if(NOT DEFINED LSYSTEM_OUTPUT_DIR)
    set(LSYSTEM_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/binaries")
endif()


########################################
## Dependencies
########################################

# Find Imath
find_package(Imath REQUIRED)

# Find usd
find_package(pxr QUIET)
if(${pxr_FOUND})
    add_definitions(-Dpxr_FOUND)
endif()


########################################
## Components
########################################

# Include src/l-SystemBase
add_subdirectory(source/l-SystemBase)

# Include src/l-SystemDraw
add_subdirectory(source/l-SystemDraw)

# Include test/l-SystemBaseTest
add_subdirectory(sandbox/l-SystemBaseTest)

# Include test/l-SystemDrawTest
add_subdirectory(sandbox/l-SystemDrawTest)
