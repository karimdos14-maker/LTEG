
cmake_minimum_required(VERSION 3.20)

project(LTEG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

add_executable(LTEG
    src/main.cpp
    src/LTEG.cpp
    src/LTEG.h
)

target_include_directories(LTEG PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(LTEG PRIVATE
    Vulkan::Vulkan
)
