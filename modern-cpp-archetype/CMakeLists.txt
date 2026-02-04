# Copyright (c) 2024 Sergio Martínez
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.20)
project(ModernCppApplication LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set verbose makefile for better debugging
set(CMAKE_VERBOSE_MAKEFILE ON)

# Find packages installed via vcpkg
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Compilation flags for debug and release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -Wextra -Wpedantic")

# Add the executable
add_executable(ModernCppApplication 
    src/main.cpp
)

# Link libraries
target_link_libraries(ModernCppApplication PRIVATE
    fmt::fmt
    spdlog::spdlog
)

# Include directories
target_include_directories(ModernCppApplication PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
