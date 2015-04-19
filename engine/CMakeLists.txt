project(pdEngine)

find_package(Epoxy)
find_package(SDL2)
find_package(SDL2_ttf)
# find_package(Spdlog)
# include(GetSpdlog)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

include_directories( 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib/include"
    ${SDL2_INCLUDE_DIR}
    ${SDL2TTF_INCLUDE_DIR} 
    ${epoxy_INCLUDE_DIR}
    #${CEGUI_INCLUDES}
    )

#file(COPY {headers} DESTINATION ${include_output_path})

add_library(pdEngine SHARED
    ${sources}
    ${headers}
    )

# add_dependencies(pdEngine libspdlog)

target_link_libraries(pdEngine
    ${SDL2_LIBRARY}
    ${SDL2TTF_LIBRARY}
    ${epoxy_LIBRARY}
    #${CEGUI_LIBRARIES}
    )

set_property(TARGET pdEngine PROPERTY CXX_STANDARD 14)
set_property(TARGET pdEngine PROPERTY CXX_STANDARD_REQUIRED ON)

file(
COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/
DESTINATION  ${include_output_path}
FILES_MATCHING PATTERN "*.h")

file(COPY ../lib/include/spdlog DESTINATION ${include_output_path})

if(${BUILD_TESTS})
    include(GetGmock)

    file(GLOB_RECURSE sources  "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

    include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/test"
        )

    add_executable(test_pdEngine ${sources})
    add_dependencies(test_pdEngine libgmock libgtest)

    target_link_libraries(test_pdEngine 
        libgmock
        libgtest
        pdEngine)

    install(TARGETS test_pdEngine DESTINATION bin)
    add_test(NAME pdEngine COMMAND test_pdEngine)
endif()

if (${pd_debug_cmake})
    message("Spdlog_INCLUDE_DIR ${Spdlog_INCLUDE_DIR}")
    message("Spdlog_LIBRARY ${Spdlog_LIBRARY}")
    message("SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR}")
    message("SDL2_LIBRARY ${SDL2_LIBRARY}")
    message("GLEW_INCLUDE_DIR ${GLEW_INCLUDE_DIR}")
    message("GLEW_LIBRARY ${GLEW_LIBRARY}")
    if (${pd_test})
        message("GTEST_LIBRARIES ${GTEST_LIBRARIES}")
        message("GMOCK_LIBRARIES ${GMOCK_LIBRARIES}")
    endif()
endif()
