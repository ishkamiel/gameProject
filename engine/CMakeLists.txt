project(pdEngine)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_package(SDL2)
find_package(Spdlog)

set(PDENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
 
include_directories( 
    ${PDENGINE_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${Spdlog_INCLUDE_DIR}
    #${CEGUI_INCLUDES}
    )

add_library(pdEngine SHARED
    ${MY_SOURCE_FILES} 
    )

target_link_libraries( 
    pdEngine 
    #pdUtils 
    ${SDL2_LIBRARY}
    #${CEGUI_LIBRARIES}
    )
