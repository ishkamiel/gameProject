include(ExternalProject)

ExternalProject_Add(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/spdlog
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND "")

add_library(libspdlog IMPORTED STATIC GLOBAL)
add_dependencies(libspdlog spdlog)

ExternalProject_Get_Property(spdlog SOURCE_DIR BINARY_DIR)
set_target_properties(libspdlog PROPERTIES
    # "IMPORTED_LOCATION" "${BINARY_DIR}/libgtest.a"
    # "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    "INTERFACE_INCLUDE_DIRECTORIES" "${SOURCE_DIR}/include"
    )
include_directories("${SOURCE_DIR}/include")
