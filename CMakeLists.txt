project(pdGameProject)

cmake_minimum_required (VERSION 2.8)

#include(SetupCompilers)

###################
# Configure stuff #
###################
set(CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake"  )

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#set(include_output_path ${PROJECT_BINARY_DIR}/include)
#set(resource_output_path ${PROJECT_BINARY_DIR}/resources)
#set(config_output_path ${PROJECT_BINARY_DIR}/config)

set(output_path ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if (NOT DEFINED output_path)
    set(output_path ${CMAKE_BINARY_DIR})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_path}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${output_path}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${output_path}/lib)
set(include_output_path ${output_path}/include)
set(resource_output_path ${output_path}/resources)
set(config_output_path ${output_path}/config)

#message(WARNING "output_path: ${output_path}")

#message(WARNING "OUTPUT ${CMAKE_OUTPUT_DIRECTORY}")
#message(WARNING "RUNTIME: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#message(WARNING "LIBRARY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

message(STATUS "Creating ${CMAKE_BUILD_TYPE} build")

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS true)
endif()

if (NOT DEFINED BUILD_DEMO)
    set(BUILD_DEMO true)
endif()


if (${BUILD_TESTS})
    message(STATUS "Including tests in build")
endif()

if (${BUILD_DEMO})
    message(STATUS "Going to build demo applications")
endif()

##################################
# Load project wide dependencies #
##################################

# Epoxy (OpenGL initialization, and stuff)
# =====
find_package(Epoxy REQUIRED)

# SDL2 (Window management, etc)
# ====
find_package(SDL2 REQUIRED)
# find_package(SDL2_ttf REQUIRED)

# CEGUI (GUI library)
# =====
# find_package(CEGUI)

# Boost (Boost...)
# =====
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS log thread date_time filesystem system REQUIRED)
#log log_setup thread date_time filesystem system

###################
# Setup compilers #
###################

# Make sure we have C++14 capabilities, yay!
set_property(GLOBAL PROPERTY CXX_STANDARD 14)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX)
    # Manually enable C++14 stuff
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

    # Warnings are nice!
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")

    # Enable debug stuff for debug stuff
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

    # Optimize...
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -o3")
endif()

#################
# Do the things #
#################

if(${BUILD_TESTS})
    enable_testing()
endif()

add_subdirectory(engine)

if(${BUILD_DEMO})
    add_subdirectory(demo)
endif()
