cmake_minimum_required(VERSION 3.14)

project(asynchronify)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_USE_RELATIVE_PATHS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

find_package(Threads REQUIRED)

add_executable(asynchronify
  asynchronify.cpp
  )

target_link_libraries(asynchronify
  GTest::gtest GTest::gtest_main
)

gtest_discover_tests(asynchronify)
