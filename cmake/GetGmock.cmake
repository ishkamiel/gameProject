# We need thread support
find_package(Threads REQUIRED)
include(ExternalProject)

ExternalProject_Add(gtest
    URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND "")

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

ExternalProject_Get_Property(gtest SOURCE_DIR BINARY_DIR)
file(MAKE_DIRECTORY "${SOURCE_DIR}/include")
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${BINARY_DIR}/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    "INTERFACE_INCLUDE_DIRECTORIES" "${SOURCE_DIR}/include"
    )
# include_directories("${SOURCE_DIR}/include")


ExternalProject_Add(gmock
    URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
    # Disable install step
    INSTALL_COMMAND "")

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)

# Set gmock properties
ExternalProject_Get_Property(gmock SOURCE_DIR BINARY_DIR)
file(MAKE_DIRECTORY "${SOURCE_DIR}/include")
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${BINARY_DIR}/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    "INTERFACE_INCLUDE_DIRECTORIES" "${SOURCE_DIR}/include"
    )
# include_directories("${SOURCE_DIR}/include")
