project (pdEngine)

cmake_minimum_required (VERSION 2.8)

#set(CMAKE_VERBOSE_MAKEFILE ON)
    
set(CMAKE_MODULE_PATH 
	"${CMAKE_SOURCE_DIR}/CMake" 
	"${CMAKE_SOURCE_DIR}/CMake/Utils" 
	"${CMAKE_SOURCE_DIR}/CMake/Packages" 
)

set (PD_ENGINE_INCLUDES "${CMAKE_SOURCE_DIR}/engine/includes")
set (PD_UTILS_INCLUDES "${CMAKE_SOURCE_DIR}/utils/includes")

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if(CMAKE_COMPILER_IS_GNUCXX)
    #set(CMAKE_CXX_COMPILER_ARG1 "-std=c++11") # Needed for Eclipse?
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_subdirectory(utils)
add_subdirectory(engine)
add_subdirectory(demo)
