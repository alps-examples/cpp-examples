cmake_minimum_required(VERSION 3.14)
project(hello-googletest)

find_package(GTest REQUIRED)

add_executable(hello-googletest
  hello-googletest.cpp
)

target_link_libraries(hello-googletest
  GTest::gtest GTest::gtest_main
)

gtest_discover_tests(hello-googletest)
