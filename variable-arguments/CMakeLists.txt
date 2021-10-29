cmake_minimum_required(VERSION 3.14)

project(variable-arguments)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

add_executable(variable-arguments
  variable-arguments.cpp
  )
