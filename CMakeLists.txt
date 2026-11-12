cmake_minimum_required(VERSION 3.20)

project(LTEG LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

set(GLFW_DIR "D:/glfw-3.5.1.bin.WIN64/glfw-3.5.1.bin.WIN64")

add_executable(LTEG
    src/main.cpp
    src/LTEG.cpp
)

target_include_directories(LTEG PRIVATE
    src
    deps/include
    "${GLFW_DIR}/include"
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL/deps/include
)

target_link_directories(LTEG PRIVATE
    "${GLFW_DIR}/lib-mingw-w64"
)

target_link_libraries(LTEG PRIVATE
    Vulkan::Vulkan
    glfw3
)
include(FetchContent)

FetchContent_Declare(
    fetch_vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG v1.4.311 
)

FetchContent_MakeAvailable(fetch_vk_bootstrap)


target_link_libraries(LTEG PRIVATE vk-bootstrap::vk-bootstrap)