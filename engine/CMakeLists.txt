file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
 
include_directories( 
    "includes"
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
    ${OGRE_Overlay_INCLUDE_DIRS}
    )

add_library ( pdEngine ${MY_HEADER_FILES} ${MY_SOURCE_FILES} )
target_link_libraries ( 
    pdEngine 
    pdUtils 
    ${OGRE_LIBRARIES}
    ${OIS_LIBRARIES}
    )
    #${OGRE_Overlay_LIBRARIES}
