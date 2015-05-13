project(pdEngineDemo)

file(GLOB MY_SOURCE_FILES       ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MY_BIN_SOURCES        ${CMAKE_CURRENT_SOURCE_DIR}/bins/*.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/src
    )

add_executable(demo ${MY_SOURCE_FILES})

target_link_libraries(demo pdEngine)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/demo.config ${config_output_path}/demo.config)

set(resource_dir ${CMAKE_CURRENT_SOURCE_DIR}/resources)

add_custom_target(demoResources ALL
        COMMAND rsync -rq ${resource_dir}/ ${resource_output_path}/demo/
        VERBATIM)

add_dependencies(demo demoResources)