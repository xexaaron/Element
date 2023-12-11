cmake_minimum_required(VERSION 3.27)
project(Window)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES Window.cpp)
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
configure_file("${CMAKE_CURRENT_LIST_DIR}/build/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/config.h")

# Create a DLL
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})