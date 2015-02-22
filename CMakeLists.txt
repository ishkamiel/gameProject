project (pdEngine)

    cmake_minimum_required (VERSION 2.8)
    
    set(CMAKE_MODULE_PATH 
    	"${CMAKE_SOURCE_DIR}/CMake" 
    	"${CMAKE_SOURCE_DIR}/CMake/Utils" 
    	"${CMAKE_SOURCE_DIR}/CMake/Packages" 
	)

    set (PD_ENGINE_INCLUDES "${CMAKE_SOURCE_DIR}/engine/includes")
    set (PD_UTILS_INCLUDES "${CMAKE_SOURCE_DIR}/utils/includes")
    
    set (PD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/build)
    set (LIBRARY_OUTPUT_PATH ${PD_OUTPUT_DIR}/lib)
    set (EXECUTABLE_OUTPUT_PATH ${PD_OUTPUT_DIR})
    
    add_subdirectory(utils)
    add_subdirectory(engine)
    add_subdirectory(demo)
