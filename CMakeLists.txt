project(pdGameProject)

cmake_minimum_required (VERSION 2.8)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()
    
set(CMAKE_MODULE_PATH 
	"${CMAKE_SOURCE_DIR}/cmake" 
)

set (PD_ENGINE_INCLUDES "${CMAKE_SOURCE_DIR}/engine/includes")
set (PD_UTILS_INCLUDES "${CMAKE_SOURCE_DIR}/utils/includes")

enable_testing()

#set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -o3")
endif()

find_package(CEGUI)
find_package(SDL)

add_subdirectory(utils)
add_subdirectory(engine)
add_subdirectory(demo)
