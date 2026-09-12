cmake_minimum_required(VERSION 3.26)

project(PONTIFEX VERSION 1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werrors")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-pedantic)
endif()

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_INSTALL_PREFIX}/share/cmake)
SET(cmake_utils ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if (NOT (DEFINED EXECUTABLE_OUTPUT_PATH) OR (EXECUTABLE_OUTPUT_PATH STREQUAL ""))
        SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/examples)
endif ()
if (NOT (DEFINED LIBRARY_OUTPUT_PATH) OR (LIBRARY_OUTPUT_PATH STREQUAL ""))
  SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib${LIBSUFFIX})
endif ()
if (NOT (DEFINED BINARY_OUTPUT_PATH) OR (BINARY_OUTPUT_PATH STREQUAL ""))
  SET (BINARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib${LIBSUFFIX})
endif ()

add_subdirectory(lib)

option(WITH_EXAMPLES OFF)
if(WITH_EXAMPLES)
    message(STATUS "COMPILE WITH EXAMPLES")
    add_subdirectory(examples)
endif()

