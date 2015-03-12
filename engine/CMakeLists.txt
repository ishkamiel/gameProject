project(pdEngine)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#find_package(SDL)
#find_package(CEGUI)
 
include_directories( 
    "include"
    "../utils/include"
    ${SDL_INCLUDES} 
    ${CEGUI_INCLUDES}
    )

add_library(pdEngine SHARED
    ${MY_HEADER_FILES} 
    ${MY_SOURCE_FILES} 
    )

target_link_libraries( 
    pdEngine 
    pdUtils 
    ${SDL_LIBRARIES}
    ${CEGUI_LIBRARIES}
    )
