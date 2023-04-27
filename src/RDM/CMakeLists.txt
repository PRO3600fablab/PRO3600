cmake_minimum_required(VERSION 3.2)
set(nomduproj "deplacements")
set(CMAKE_BUILD_TYPE Debug)

project(${nomduproj})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories(/usr/include/eigen3)

#add_executable(${nomduproj} "déplacements.cpp")
add_executable(assemblage assemblage.cpp)
