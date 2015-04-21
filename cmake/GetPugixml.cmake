include(ExternalProject)

set(dir ${CMAKE_CURRENT_BINARY_DIR}/pugixml)
set(patch ${CMAKE_SOURCE_DIR}/misc/pugixml.patch)

set(cp_src ${dir}/src/pugixml/scripts/CMakeLists.txt)
set(cp_dst ${dir}/src/pugixml/CMakeLists.txt)

ExternalProject_Add(pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.6
    # URL http://github.com/zeux/pugixml/releases/download/v1.6/pugixml-1.6.tar.gz
    PREFIX ${dir}
    PATCH_COMMAND patch -p0 -d ${dir}/src/pugixml < ${patch} && cp ${cp_src} ${cp_dst}
    INSTALL_COMMAND "")

add_library(libpugixml IMPORTED STATIC GLOBAL)
add_dependencies(libpugixml pugixml)

ExternalProject_Get_Property(pugixml SOURCE_DIR BINARY_DIR)
file(MAKE_DIRECTORY "${SOURCE_DIR}/include")
set_target_properties(libpugixml PROPERTIES
    "IMPORTED_LOCATION" "${BINARY_DIR}/libpugixml.a"
    "INTERFACE_INCLUDE_DIRECTORIES" "${SOURCE_DIR}/include"
    )
# include_directories("${SOURCE_DIR}/include")

