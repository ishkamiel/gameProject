project(pdEngine VERSION 0.0.1 LANGUAGES CXX)

# Some variables for cleaner setup
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(test_dir ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(resource_dir ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(config_dir ${CMAKE_CURRENT_SOURCE_DIR}/config)

# Fetch pugixml...
include(GetPugixml)

# Find source files to compile
file(GLOB_RECURSE sources ${source_dir}/*.cpp)

# include directories
include_directories(${include_output_path} ${include_dir} ${source_dir}
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

# configure the build_option.h header file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/build_options.h
    ${include_output_path}/build_options.h
)

# add target for config fiels
configure_file(${config_dir}/engine.config ${config_output_path}/${PDE_CONFIG_FILENAME})

# copy header files to include output directory
#file(COPY ${include_dir}/ DESTINATION  ${include_output_path} FILES_MATCHING PATTERN "*.h")

#################
# Documentation #
#################

if(DOXYGEN_FOUND)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    set(my_docpath ${doc_output_path}/engine)

    add_custom_target(docEnginePaths COMMAND mkdir -p ${my_docpath})

    add_custom_target(docEngine
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        DEPENDS docEnginePaths
        WORKING_DIRECTORY ${my_docpath}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        ) 

    add_dependencies(doc docEngine)

endif(DOXYGEN_FOUND)

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
        COMMAND rsync -rq ${resource_dir}/testResourceDir ${resource_output_path}
        VERBATIM)

    # configure testing.config file
    configure_file(${config_dir}/testing.config ${config_output_path}/testing.config)

    # add dependancies to ensure resources are moved
    add_dependencies(test_pdEngine testResources pdEngine)

    # make CMake testing facilities aware of test_pdEngine
    add_test(NAME pdEngine COMMAND test_pdEngine)

endif()
