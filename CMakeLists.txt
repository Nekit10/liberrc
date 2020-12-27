cmake_minimum_required(VERSION 3.15)
project(liberrc)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(unittests)

add_library(liberrc INTERFACE)
target_include_directories(liberrc INTERFACE liberrc)
SET_TARGET_PROPERTIES(name PROPERTIES PREFIX "")