cmake_minimum_required(VERSION 3.14)

project(digit-separators)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_USE_RELATIVE_PATHS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

add_executable(digit-separators
  digit-separators.cpp
  )
