# Specify the minimum version of CMake required to process this file
cmake_minimum_required(VERSION 3.21)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Enforce the use of the specified C++ standard (C++20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set target architectures based on the operating system
# If building for iOS or the IOS variable is set, use only arm64 architecture
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
# Otherwise, build for both arm64 and x86_64 (for macOS universal binaries)
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

# Hide symbols by default unless explicitly marked for export (improves binary encapsulation)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Define the project and its version
project(EchoPort VERSION 1.0.0)

# Recursively find all .cpp source files inside the src directory
# CONFIGURE_DEPENDS allows CMake to re-evaluate if source files change
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Define a shared library target named after the project and use the collected source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Check if the GEODE_SDK environment variable is defined
# If not defined, abort the configuration with an error message
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
# If defined, print a message stating where the SDK was found
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Add the Geode SDK as a subdirectory, building it inside the current binary directory under "geode"
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Use a Geode-provided function to configure the current project as a Geode mod
setup_geode_mod(${PROJECT_NAME})