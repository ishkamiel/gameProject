project(pdEngineDemo)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB MY_BIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/bins/*.cpp")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
	${include_output_path}
    )

foreach(BIN_SOURCE ${MY_BIN_SOURCES})
    string(REGEX REPLACE "^.*/(.*)\\.cpp$" "\\1"
        bin_name
        ${BIN_SOURCE})

    add_executable(${bin_name} ${BIN_SOURCE}
        ${MY_HEADER_FILES} ${MY_SOURCE_FILES})

    target_link_libraries(${bin_name} pdEngine)
endforeach(BIN_SOURCE)
