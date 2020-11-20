cmake_minimum_required(VERSION 3.17)
project(LABA_5)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(LABA_5 calc.cpp calc.h calc_tests.cpp)
# add_executable(LABA_5 date.cpp date.h date_tests.cpp)
target_link_libraries(LABA_5 gtest gtest_main)