cmake_minimum_required(VERSION 3.10)
project(LTEG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(src)

add_executable(LTEG src/main.cpp src/LTEG.cpp)