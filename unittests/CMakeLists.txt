cmake_minimum_required(VERSION 3.15)
project(unittests)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../)

add_executable(ErrorValueTests errv_tests.cpp ../errc.h)
target_link_libraries(ErrorValueTests gtest gtest_main)