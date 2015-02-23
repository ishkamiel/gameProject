project (pdEngine)

cmake_minimum_required (VERSION 2.8)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
    
set(CMAKE_MODULE_PATH 
	"${CMAKE_SOURCE_DIR}/CMake" 
	"${CMAKE_SOURCE_DIR}/CMake/Utils" 
	"${CMAKE_SOURCE_DIR}/CMake/Packages" 
)

set (PD_ENGINE_INCLUDES "${CMAKE_SOURCE_DIR}/engine/includes")
set (PD_UTILS_INCLUDES "${CMAKE_SOURCE_DIR}/utils/includes")
    
set (PD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/build)
set (LIBRARY_OUTPUT_PATH ${PD_OUTPUT_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${PD_OUTPUT_DIR}/bin)

if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set ( CMAKE_INSTALL_PREFIX ${PD_OUTPUT_DIR} )
#set ( CMAKE_DEBUG_POSTFIX "_d" )

include(SetupOgre)
    
add_subdirectory(utils)
add_subdirectory(engine)
add_subdirectory(demo)

#file(COPY
	#${CMAKE_CURRENT_SOURCE_DIR}/assets
    #DESTINATION ${PD_OUTPUT_DIR}
    #)
