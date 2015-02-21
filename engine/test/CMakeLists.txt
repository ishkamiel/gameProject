find_library(CppUnit REQUIRED)
include_directories(${CppUnit_INCLUDE_DIRS})
set(TEST_LIBS ${TEST_LIBS} ${CppUnit_LIBRARIES})

#make file flags:T_LD_FLAGS = $(LD_FLAGS) -Wl,--no-as-needed -lcppunit

add_subdirectory(utils)
add_executable(run_tests run_tests.cpp)
target_link_libraries(run_tests ${TEST_LIBS})
