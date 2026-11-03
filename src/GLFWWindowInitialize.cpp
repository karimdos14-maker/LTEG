#include "GLFWWindowInitialize.h"
#include <iostream>
int GlfWWI::GlfwIWW()
{
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed!\n";
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(
        1280,
        720,
        "LTEG Engine",
        nullptr,
        nullptr);

    if (!window)
    {
        std::cout << "Window creation failed!\n";
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
