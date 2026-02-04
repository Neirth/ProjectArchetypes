// Copyright (c) 2024 Sergio Martínez
// SPDX-License-Identifier: MIT

/**
 * @file main.cpp
 * @brief Entry point for the Modern C++ Application
 * @author Sergio Martínez
 * 
 * This file contains the main function that serves as the entry point
 * for the Modern C++ Application archetype. It demonstrates the use
 * of modern C++ features and vcpkg package management.
 */

#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <iostream>

/**
 * @brief Main entry point of the application
 * 
 * Initializes the application and demonstrates basic usage of
 * fmt and spdlog libraries installed via vcpkg.
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return int Exit code (0 for success)
 */
int main(int argc, char* argv[]) {
    // Initialize logging
    spdlog::info("Modern C++ Application started");
    spdlog::info("Command-line arguments: {}", argc);
    
    // Demonstrate fmt usage
    std::string message = fmt::format("Hello from Modern C++ Application!");
    spdlog::info(message);
    
    // Process command-line arguments
    for (int i = 0; i < argc; ++i) {
        spdlog::debug("Argument {}: {}", i, argv[i]);
    }
    
    spdlog::info("Application completed successfully");
    return 0;
}
