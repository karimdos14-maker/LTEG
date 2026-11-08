cmake_minimum_required(VERSION 3.20)

project(LTEG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

set(GLFW_DIR "D:/glfw-3.5.1.bin.WIN64/glfw-3.5.1.bin.WIN64")

add_executable(LTEG
    src/main.cpp
    src/LTEG.cpp
    vulkini/vulkann.cpp
)

target_include_directories(LTEG PRIVATE
    src
    vulkini
    "${GLFW_DIR}/include"
)

target_link_directories(LTEG PRIVATE
    "${GLFW_DIR}/lib-mingw-w64"
)

target_link_libraries(LTEG PRIVATE
    Vulkan::Vulkan
    glfw3
)
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui-master")

target_sources(LTEG PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
)


target_include_directories(LTEG PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
