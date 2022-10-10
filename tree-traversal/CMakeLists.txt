cmake_minimum_required(VERSION 3.14)

project(tree-traversal)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

add_executable(tree-traversal
  tree-traversal.cpp
)

target_link_libraries(tree-traversal
  GTest::gtest GTest::gtest_main
)

gtest_discover_tests(tree-traversal)
