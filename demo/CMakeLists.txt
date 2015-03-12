project(pdEngineDemo)

file(GLOB MY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB MY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories( 
	"include" 
    "../engine/include"
    "../utils/include"
	${PD_ENGINE_INCLUDES} 
    ${PD_UTILS_INCLUDES} 
    )

add_executable (demo ${MY_HEADER_FILES} ${MY_SOURCE_FILES})
target_link_libraries(demo 
    pdUtils 
    pdEngine 
    )

# file(COPY
#     ${CMAKE_CURRENT_SOURCE_DIR}/config/plugins.cfg
#     ${CMAKE_CURRENT_SOURCE_DIR}/config/resources.cfg
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#     )
#
# file(COPY
#     ${CMAKE_CURRENT_SOURCE_DIR}/assets
#     DESTINATION ${CMAKE_BINARY_DIR}
#     )
