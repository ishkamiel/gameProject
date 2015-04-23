project(pdGameProject)

cmake_minimum_required (VERSION 2.8)

set(CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake"  )
set(pd_debug_cmake false) # enables some extra cmake output
include(SetupDefaults)
include(SetupCompilers)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(include_output_path ${PROJECT_BINARY_DIR}/include)

##################################
# Load project wide dependencies #
##################################

# Epoxy
# =====
find_package(Epoxy REQUIRED)

# SDL2
# ====
find_package(SDL2 REQUIRED)
# find_package(SDL2_ttf REQUIRED)

# Boost
# =====
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS log thread date_time filesystem system REQUIRED)
#log log_setup thread date_time filesystem system

#################
# Do the things #
#################

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(engine)
if (BUILD_DEMO)
    add_subdirectory(demo)
endif()

#enable_testing()
