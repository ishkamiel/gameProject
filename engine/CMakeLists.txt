file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories( "includes" )

set ( EXTERNAL_LIBRARIES glut GL GLU )

add_library ( pdEngine ${MY_HEADER_FILES} ${MY_SOURCE_FILES} )
target_link_libraries ( pdEngine pdUtils ${EXTERNAL_LIBRARIES} )
