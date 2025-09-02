cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(Astral VERSION 1.0.0)

# Include CPM (should be done before using CPMAddPackage)
include(cmake/CPM.cmake)

# Find Geode SDK
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Set CMAKE_PREFIX_PATH to include Geode SDK so find_package can locate it
set(CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}" ${CMAKE_PREFIX_PATH})

# Add Geode
find_package(geode REQUIRED)

# Get source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the mod library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Add imgui-cocos dependency
CPMAddPackage("gh:matcool/gd-imgui-cocos#bc342a8")
target_link_libraries(${PROJECT_NAME} imgui-cocos)

# Setup Geode mod (this should come after target creation and dependencies)
setup_geode_mod(${PROJECT_NAME})