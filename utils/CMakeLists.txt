file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("includes")

add_library(pdUtils SHARED
    ${MY_HEADER_FILES} 
    ${MY_SOURCE_FILES} 
    )

file(GLOB MY_TEST_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")
file(GLOB MY_TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

find_package(CppUnit)

add_executable(testUtils
    ${MY_TEST_HEADER_FILES} 
    ${MY_TEST_SOURCE_FILES} 
    )

target_link_libraries(testUtils
    pdUtils
    ${CppUnit_LIBRARIES}
    )
