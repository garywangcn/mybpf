IF (UNIX AND NOT APPLE)
cmake_minimum_required(VERSION 2.8)
ENDIF()
IF (APPLE OR WIN32)
cmake_minimum_required(VERSION 3.2)
ENDIF()

INCLUDE(${CMAKE_SOURCE_DIR}/my_cmake_def.txt)

project (mysys)

include_directories(./h)

# utl
add_subdirectory(./src/lib/util)

IF (WIN32)
include_directories(../open/h)
add_subdirectory(./src_win/lib/util)
ENDIF ()

# base
add_subdirectory(./src/lib/base)

# tools
add_subdirectory(./src/tool)

IF (WIN32)
set(CMAKE_C_FLAGS "/utf-8 ${CMAKE_C_FLAGS}")
ENDIF()

