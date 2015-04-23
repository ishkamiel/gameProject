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
        BIN_FILENAME
        ${BIN_SOURCE})

    add_executable(${BIN_FILENAME} ${BIN_SOURCE} 
        ${MY_HEADER_FILES} ${MY_SOURCE_FILES})

    target_link_libraries(${BIN_FILENAME}
        pdEngine)

endforeach(BIN_SOURCE)

if (${pd_debug_cmake})
    message("demo")
    message("Spdlog_INCLUDE_DIR ${Spdlog_INCLUDE_DIR}")
    message("Spdlog_LIBRARY ${Spdlog_LIBRARY}")
    message("SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR}")
    message("SDL2_LIBRARY ${SDL2_LIBRARY}")
    message("GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIR}")
    message("GLEW_LIBRARY ${GLEW_LIBRARY}")
    message("Boost_LIBRARIES: ${Boost_LIBRARIES}")
    if (${pd_test})
        message("GTEST_LIBRARIES ${GTEST_LIBRARIES}")
        message("GMOCK_LIBRARIES ${GMOCK_LIBRARIES}")
    endif()
endif()
