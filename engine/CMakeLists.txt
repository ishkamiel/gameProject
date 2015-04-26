project(pdEngine)

include(GetPugixml)

# Some variables for cleaner setup
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(test_dir ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(resource_dir ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Find source files to compile
file(GLOB_RECURSE sources ${source_dir}/*.cpp)

# include directories
include_directories(${include_dir} ${source_dir}
    ${SDL2_INCLUDE_DIR}
    ${epoxy_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR})

# add the enginge library itself
add_library(pdEngine STATIC ${sources})

# add dependencies to make sure they are compiled too
add_dependencies(pdEngine libpugixml)

# link to appropriate external libraries
target_link_libraries(pdEngine
    ${SDL2_LIBRARY}
    ${epoxy_LIBRARY}
    ${Boost_LIBRARIES})

# copy header files to include output directory
file(COPY ${include_dir}/ DESTINATION  ${include_output_path} FILES_MATCHING PATTERN "*.h")

#################
# Testing stuff #
#################

if(${BUILD_TESTS})
    # get gmock and gtest
    include(GetGmock)

    # find test files to compile
    file(GLOB_RECURSE test_sources ${test_dir}/*.cpp)

    # include all engine directories
    include_directories(${include_dir} ${source_dir} ${test_dir})

    add_executable(test_pdEngine ${test_sources})
    #add_dependencies(test_pdEngine libgmock libgtest pdEngine)

    # link to the engine and testing libraries
    target_link_libraries(test_pdEngine libgmock libgtest pdEngine)

    # add target for testing resources
    add_custom_target(testResources ALL
        COMMAND rsync -rq ${resource_dir}/test ${resource_output_path} VERBATIM)

    # add dependancies to ensure resources are moved
    add_dependencies(test_pdEngine testResources pdEngine)

    # make CMake testing facilities aware of test_pdEngine
    add_test(NAME pdEngine COMMAND test_pdEngine)

endif()
