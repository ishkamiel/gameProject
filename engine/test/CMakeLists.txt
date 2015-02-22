find_package (CppUnit)

set(TEST_LIBS ${TEST_LIBS} ${CPPuNIT_LIBRARIES})

add_subdirectory ( utils )

add_executable(run_tests run_tests.cpp)


target_link_libraries(run_tests ${CPPUNIT_LIBRARIES})