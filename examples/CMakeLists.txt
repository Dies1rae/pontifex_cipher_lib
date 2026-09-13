cmake_minimum_required(VERSION 3.26)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-pedantic)
endif()

SET( SRC
    pontifex_cipher.cpp  
  )

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}../lib/
  )

SET(LIBS
  pontifex
  )

add_executable(pontifexcmd ${SRC})

TARGET_LINK_LIBRARIES( pontifexcmd
  ${LIBS}
  stdc++fs
  )

INSTALL(TARGETS pontifexcmd DESTINATION ${EXECUTABLE_OUTPUT_PATH})

