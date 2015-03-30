project(pdEngine)

file(GLOB_RECURSE MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_package(GLEW)
find_package(SDL2)
find_package(SDL2_ttf)
find_package(Spdlog)
find_package(CppUnit)

set(PDENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
 
include_directories( 
    ${PDENGINE_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2TTF_INCLUDE_DIR} 
    ${Spdlog_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR} 
    #${CEGUI_INCLUDES}
    )

add_library(pdEngine SHARED
    ${MY_SOURCE_FILES} 
    )

target_link_libraries(pdEngine 
    ${SDL2_LIBRARY}
    ${SDL2TTF_LIBRARY}
    ${GLEW_LIBRARY} 
    #${CEGUI_LIBRARIES}
    )


if(${CppUnit_FOUND})
    file(GLOB MY_TEST_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")
    file(GLOB MY_TEST_BIN_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/test/*_test.cpp")

    foreach(BIN_SOURCE ${MY_TEST_BIN_SOURCES})
        string(REGEX REPLACE "^.*/(.*)\\_test.cpp$" "test_\\1"
            BIN_FILENAME
            ${BIN_SOURCE})

        string(REGEX REPLACE "^.*/(.*)\\_test.cpp$" "\\1"
            TEST_NAME
            ${BIN_SOURCE})

        add_executable(${BIN_FILENAME} ${BIN_SOURCE})

        target_link_libraries(${BIN_FILENAME} ${CppUnit_LIBRARIES} pdEngine)

        add_test(NAME ${TEST_NAME} COMMAND ${BIN_FILENAME})
    endforeach(BIN_SOURCE)
endif()

# message("SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR}")
# message("SDL2_LIBRARY ${SDL2_LIBRARY}")
# message("GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIR}")
# message("GLEW_LIBRARY ${GLEW_LIBRARY}")
