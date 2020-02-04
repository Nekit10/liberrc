project(unittests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(ErrorValueTests test1.cpp tests2.cpp)
#target_link_libraries(ErrorValueTests gtest gtest_main)