cmake_minimum_required(VERSION 3.19.3)

project (TerminalSnake)

add_subdirectory(CLI_renderer_lib)

file(GLOB_RECURSE _HDRFILES ${CMAKE_CURRENT_SOURCE_DIR}/header_files/*.h)
file(GLOB_RECURSE _SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

source_group("Header Files" FILES ${_HDRFILES})
source_group("Source Files" FILES ${_SRCFILES})

add_executable(TerminalSnake ${_HDRFILES} ${_SRCFILES} ${_LIBSOURCE} ${_LIBHEADERS})


