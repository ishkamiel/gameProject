project(pdGameProject)

cmake_minimum_required (VERSION 2.8)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()
    
set(CMAKE_MODULE_PATH 
	"${CMAKE_SOURCE_DIR}/cmake" 
)

SET(pd_debug_cmake true)
SET(pd_test true)
SET(pd_demo false)

# set(PD_EXTERNAL_LIBRARIES "${CMAKE_SOURCE_DIR}/lib")
# set(PD_ENGINE_INCLUDES "${CMAKE_SOURCE_DIR}/engine/includes")

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -o3")
endif()

if(pd_test)
    # include(GetGmock)
    message("Going to building tests")
    enable_testing()
endif()

add_subdirectory(engine)
if (pd_demo)
    add_subdirectory(demo)
endif()
enable_testing()
