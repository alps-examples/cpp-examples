cmake_minimum_required(VERSION 3.14)

project(parallel-sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_EXTENSIONS AND MSVC)
  add_compile_options(/permissive-)
endif()

find_package(TBB REQUIRED)

add_executable(parallel-sort
  parallel-sort.cpp
  )

target_link_libraries(parallel-sort
  PRIVATE TBB::tbb)
