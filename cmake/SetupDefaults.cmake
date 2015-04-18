if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS true)
endif()

if (NOT DEFINED BUILD_DEMO)
    set(BUILD_DEMO true)
endif()

message(STATUS "Config: CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}'")
message(STATUS "Config: BUILD_TESTS: '${BUILD_TESTS}'")
message(STATUS "Config: BUILD_DEMO: '${BUILD_DEMO}'")
