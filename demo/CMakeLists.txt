project(pdEngineDemo)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_package(SDL2)

include_directories( 
	"include" 
    "../engine/include"
    ${SDL2_INCLUDE_DIR} 
    )

add_executable (demo ${MY_HEADER_FILES} ${MY_SOURCE_FILES})
target_link_libraries(demo 
    pdEngine 
    ${SDL2_LIBRARY}
    )
