project(pdEngine)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_package(OGRE)
find_package(CEGUI)
find_package(OIS)
 
include_directories( 
    "includes"
    ${PD_UTILS_INCLUDES} 
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
    #${OGRE_Overlay_INCLUDE_DIRS}
    ${CEGUI_INCLUDE_DIRS}
    )

add_library(pdEngine SHARED
    ${MY_HEADER_FILES} 
    ${MY_SOURCE_FILES} 
    )

target_link_libraries( 
    pdEngine 
    pdUtils 
    ${OIS_LIBRARIES}
    ${OGRE_LIBRARIES}
    #${OGRE_Overlay_LIBRARIES}
    ${CEGUI_LIBRARIES}
    )
