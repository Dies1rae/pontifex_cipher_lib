cmake_minimum_required(VERSION 3.26)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wsign-conversion -Weffc++")

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-pedantic)
endif()

set( SRCS
  pontifex.cpp
  pontifex.h
  )

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

ADD_LIBRARY ( pontifex SHARED
  ${SRCS}
  )

TARGET_LINK_LIBRARIES( pontifex
)

TARGET_INCLUDE_DIRECTORIES(pontifex
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS pontifex LIBRARY DESTINATION ${LIB_INSTALL_DIR} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
