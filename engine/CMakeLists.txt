project (pdEngine)

    cmake_minimum_required (VERSION 2.8)
    
    set(CMAKE_MODULE_PATH 
    	"${CMAKE_SOURCE_DIR}/CMake" 
    	"${CMAKE_SOURCE_DIR}/CMake/Utils" 
    	"${CMAKE_SOURCE_DIR}/CMake/Packages" 
	)
    
    set (MAIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/build)
    set (LIBRARY_OUTPUT_PATH ${MAIN_OUTPUT_DIR}/lib)
    set (EXECUTABLE_OUTPUT_PATH ${MAIN_OUTPUT_DIR})

    message("Using output dir: ${MAIN_OUTPUT_DIR}")
    
    add_subdirectory(src)
    add_subdirectory(demo)
    add_subdirectory(test)
