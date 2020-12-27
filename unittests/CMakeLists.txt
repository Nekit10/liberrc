cmake_minimum_required(VERSION 3.15)
project(unittests)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../liberrc)

add_executable(ErrorValueTests errv_tests.cpp ../liberrc/liberrc.h)
add_executable(ErrorValueMathTests errmath_tests.cpp ../liberrc/liberrc.h)

target_link_libraries(ErrorValueTests gtest gtest_main)
target_link_libraries(ErrorValueMathTests gtest gtest_main)