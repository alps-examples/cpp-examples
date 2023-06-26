cmake_minimum_required(VERSION 3.14)

project(mutexes)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

add_executable(mutexes
  mutexes.cpp
)

target_link_libraries(mutexes
  GTest::gtest GTest::gtest_main
)

gtest_discover_tests(mutexes)
