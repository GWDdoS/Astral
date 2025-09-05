cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Astral VERSION 1.0.0)

# Include CPM (should be done before using CPMAddPackage)
# include(cmake/CPM.cmake)

# Find Geode SDK
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Add Geode SDK as subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Get source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the mod library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Add imgui-cocos dependency
CPMAddPackage("gh:matcool/gd-imgui-cocos##bc342a8")
target_link_libraries(${PROJECT_NAME} imgui-cocos)

# Setup Geode mod (this should come after target creation and dependencies)
setup_geode_mod(${PROJECT_NAME})