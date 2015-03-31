project(pdEngine)


find_package(GLEW)
find_package(SDL2)
find_package(SDL2_ttf)
find_package(Spdlog)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories( 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ${SDL2_INCLUDE_DIR} 
    ${SDL2TTF_INCLUDE_DIR} 
    ${Spdlog_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR} 
    #${CEGUI_INCLUDES}
    )

add_library(pdEngine SHARED
    ${sources} 
    )

target_link_libraries(pdEngine
    ${SDL2_LIBRARY}
    ${SDL2TTF_LIBRARY}
    ${GLEW_LIBRARY} 
    #${CEGUI_LIBRARIES}
    )

if(${pd_test})
    # find_package(Gmock)
    include(GetGmock)

    file(GLOB_RECURSE sources  "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

    include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/test"
        )

    add_executable(test_pdEngine ${sources})

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
