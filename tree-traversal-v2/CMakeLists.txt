cmake_minimum_required(VERSION 3.14)

project(tree-traversal-v2)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

add_executable(tree-traversal-v2
  tree-traversal-v2.cpp
)

target_link_libraries(tree-traversal-v2
  GTest::gtest GTest::gtest_main
)

gtest_discover_tests(tree-traversal-v2)
