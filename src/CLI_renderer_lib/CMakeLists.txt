cmake_minimum_required(VERSION 3.19.3)

project (TerminalSnake)

file(GLOB_RECURSE _LIBHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE _LIBSOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group("Lib source" FILES ${_LIBSOURCE})
source_group("Lib headers" FILES ${_LIBHEADERS})
