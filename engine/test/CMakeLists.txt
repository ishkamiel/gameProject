find_package (CppUnit)

add_subdirectory ( utils )

add_executable(run_tests run_tests.cpp)

target_link_libraries(run_tests TestUtils ${CppUnit_LIBRARIES})