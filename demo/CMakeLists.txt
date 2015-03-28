project(pdEngineDemo)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

file(GLOB MY_BIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/bins/*.cpp")

find_package(SDL2)

include_directories( 
	"include" 
    "../engine/include"
    ${SDL2_INCLUDE_DIR} 
    )

foreach(BIN_SOURCE ${MY_BIN_SOURCES})
    string(REGEX REPLACE "^.*/(.*)\\.cpp$" "\\1"
        BIN_FILENAME
        ${BIN_SOURCE})

    # message("Creating binary ${BIN_FILENAME}")

    add_executable(${BIN_FILENAME} ${BIN_SOURCE} 
        ${MY_HEADER_FILES} ${MY_SOURCE_FILES})

    target_link_libraries(${BIN_FILENAME}
        ${SDL2_LIBRARY}
        pdEngine)

endforeach(BIN_SOURCE)
