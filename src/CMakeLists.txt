cmake_minimum_required(VERSION 3.19.3)

project (TerminalSnake)


file(GLOB_RECURSE _HDRFILES ${CMAKE_CURRENT_SOURCE_DIR}/header_files/*.h)
file(GLOB_RECURSE _SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE _LIBHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/CLI_renderer_lib*.h)
file(GLOB_RECURSE _LIBSOURCE ${CMAKE_CURRENT_SOURCE_DIR}/CLI_renderer_lib*.cpp)

source_group("Header Files" FILES ${_HDRFILES})
source_group("Source Files" FILES ${_SRCFILES})

source_group("Lib source" FILES ${_LIBSOURCE})
source_group("Lib headers" FILES ${_LIBHEADERS})

add_executable(TerminalSnake ${_HDRFILES} ${_SRCFILES} ${_LIBSOURCE} ${_LIBHEADERS})

if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif(UNIX)