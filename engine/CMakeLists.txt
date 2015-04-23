project(pdEngine)

include(GetPugixml)

# Some variables for cleaner setup
set(source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(header_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Find *.cpp files and *.h files
file(GLOB_RECURSE sources ${source_dir}/*.cpp)
file(GLOB_RECURSE headers ${header_dir}/*.h)

# include directories
include_directories(${header_dir}
    ${SDL2_INCLUDE_DIR}
    ${epoxy_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR})

# add the enginge library itself
add_library(pdEngine STATIC ${sources} ${headers})

# add dependencies to make sure they are compiled too
add_dependencies(pdEngine libpugixml)

# link to appropriate external libraries
target_link_libraries(pdEngine
    ${SDL2_LIBRARY}
    ${epoxy_LIBRARY}
    ${Boost_LIBRARIES})

# copy header files to include output directory
file(COPY ${header_dir}/
     DESTINATION  ${include_output_path}
     FILES_MATCHING PATTERN "*.h")

#################
# Testing stuff #
#################

if(${BUILD_TESTS})
    # get gmock and gtest
    include(GetGmock)

    # find test files to compile
    file(GLOB_RECURSE sources  "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

    # include all engine directories
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/test
        #${Boost_INCLUDE_DIR}
        )

    add_executable(test_pdEngine ${sources})
    #add_dependencies(test_pdEngine libgmock libgtest pdEngine)

    # link to the engine and testing libraries
    target_link_libraries(test_pdEngine  libgmock libgtest pdEngine)

    #install(TARGETS test_pdEngine DESTINATION bin)

    # make CMake testing facilities aware of test_pdEngine
    # add_test(NAME pdEngine COMMAND test_pdEngine)
endif()
