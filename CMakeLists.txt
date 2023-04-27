cmake_minimum_required(VERSION 3.2)
project(Pro3600)
add_subdirectory(src)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()