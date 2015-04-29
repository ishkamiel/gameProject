project(pdEngineDemo)

file(GLOB MY_SOURCE_FILES       ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MY_BIN_SOURCES        ${CMAKE_CURRENT_SOURCE_DIR}/bins/*.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/src
    )

# create a binary for each source file in the bins directory
foreach(BIN_SOURCE ${MY_BIN_SOURCES})
    # create binary name by dropping extension
    string(REGEX REPLACE "^.*/(.*)\\.cpp$" "\\1" bin_name ${BIN_SOURCE})

    # add an executable target for binary
    add_executable(${bin_name} ${BIN_SOURCE} ${MY_SOURCE_FILES})

    # link target to the pdEngine library
    target_link_libraries(${bin_name} pdEngine)
endforeach(BIN_SOURCE)
