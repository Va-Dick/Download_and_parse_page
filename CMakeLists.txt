cmake_minimum_required (VERSION 2.6)

project (cmake_project_1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

file(GLOB CPP_SOURCES "src/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})