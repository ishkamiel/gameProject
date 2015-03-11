project(pdUtils)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories("include")

add_library(pdUtils SHARED
    ${MY_HEADER_FILES} 
    ${MY_SOURCE_FILES} 
    )

find_package(CppUnit)

if(${CppUnit_FOUND})
    file(GLOB MY_TEST_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")
    file(GLOB MY_TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

    add_executable(test_pdUtils
        ${MY_TEST_HEADER_FILES} 
        ${MY_TEST_SOURCE_FILES} 
        )

    target_link_libraries(test_pdUtils
        pdUtils
        ${CppUnit_LIBRARIES}
        )

    add_test(NAME pdUtils COMMAND test_pdUtils)
endif()
