# CMakeLists.txt

cmake_minimum_required(VERSION 3.27)
project(Element)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp
                 src/Global/IO.hpp
                 src/Base/Class.cpp)

configure_file("${CMAKE_CURRENT_LIST_DIR}/build/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/config.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
