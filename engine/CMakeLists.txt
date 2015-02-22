project (pdEngine)

    cmake_minimum_required (VERSION 2.8)
    
    set(CMAKE_MODULE_PATH 
    	"${OGRE_SOURCE_DIR}/CMake" 
    	"${OGRE_SOURCE_DIR}/CMake/Utils" 
    	"${OGRE_SOURCE_DIR}/CMake/Packages" 
	)

    list(APPEND CMAKE_CXX_FLAGS "-std=c++0x")

    set (CMAKE_BUILD_TYPE Debug)
    set (MAIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/build)
    set (LIBRARY_OUTPUT_PATH ${MAIN_OUTPUT_DIR}/lib)
    set (EXECUTABLE_OUTPUT_PATH ${MAIN_OUTPUT_DIR})

    message("Using output dir: ${MAIN_OUTPUT_DIR}")
    
    add_subdirectory(src)
    add_subdirectory(demo)
    #add_subdirectory(test)
