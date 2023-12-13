cmake_minimum_required(VERSION 3.27)
project(Element)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_FILES main.cpp
                 src/Global/IO.hpp
                 src/Base/Base.cpp
                 src/Application/Application.cpp
                 src/Application/Window.cpp)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif()

if (${VERBOSE} STREQUAL "true")
    add_compile_definitions(VERBOSE)
endif()

if (${LOGGING} STREQUAL "true")
    add_compile_definitions(LOGGING)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(LIB_PREFIX "")
    set(LIB_EXT ".dll")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(LIB_PREFIX "[Not Implemented]")
    set(LIB_EXT ".[Not Implemented]")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LIB_PREFIX "lib")
    set(LIB_EXT ".so")
else()
    message("ERROR : Operating system not supported")
endif()

configure_file("${CMAKE_CURRENT_LIST_DIR}/build/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/config.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

