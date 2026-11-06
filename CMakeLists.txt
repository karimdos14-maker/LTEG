
cmake_minimum_required(VERSION 3.20)

project(LTEG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

add_executable(LTEG
    src/main.cpp
    src/LTEG.cpp
    src/LTEG.h
    Vulkan/vulkann.cpp
)

target_include_directories(LTEG PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(LTEG PRIVATE
    Vulkan::Vulkan
)

set(GLFW_DIR "D:/glfw-3.5.1.bin.WIN64/glfw-3.5.1.bin.WIN64")

target_include_directories(LTEG PRIVATE
    "${GLFW_DIR}/include"
)

target_link_directories(LTEG PRIVATE
    "${GLFW_DIR}/lib-mingw-w64"
)

target_link_libraries(LTEG PRIVATE
    glfw3
)