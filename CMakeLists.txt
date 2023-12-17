cmake_minimum_required(VERSION 3.27)
project(Element)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES 
# C++ Source Files
    main.cpp
    src/Global/IO.hpp
    src/Base/Base.cpp
    src/Application/Window.cpp
# C   Source Files
    #
)

include("${CMAKE_CURRENT_LIST_DIR}/build/Build-Mode.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/build/Flags.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/build/Platform.cmake")


configure_file("${CMAKE_CURRENT_LIST_DIR}/build/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/config.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


