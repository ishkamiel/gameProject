include(ExternalProject)

set(dir ${CMAKE_CURRENT_BINARY_DIR}/epoxy)

ExternalProject_Add(epoxy
    GIT_REPOSITORY https://github.com/anholt/libepoxy.git
    GIT_TAG v1.2
    PREFIX ${dir}
    PATCH_COMMAND ""
    CONFIGURE_COMMAND "autogen.sh"
    BUILD_COMMAND "make"
    UPDATE_COMMAND ""
    INSTALL_COMMAND "")

add_library(libepoxy IMPORTED STATIC GLOBAL)
add_dependencies(libepoxy epoxyk)

ExternalProject_Get_Property(epoxy SOURCE_DIR BINARY_DIR)
file(MAKE_DIRECTORY "${SOURCE_DIR}/include")
set_target_properties(libepoxy PROPERTIES
    "INTERFACE_INCLUDE_DIRECTORIES" "${SOURCE_DIR}/src"
    )
include_directories("${SOURCE_DIR}/src")
