project(pdGameProject)

cmake_minimum_required (VERSION 2.8)

set(CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake"  )
set(pd_debug_cmake false)
include(SetupDefaults)
include(SetupCompilers)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(include_output_path ${PROJECT_BINARY_DIR}/include)

if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(engine)
if (BUILD_DEMO)
    add_subdirectory(demo)
endif()

#enable_testing()
