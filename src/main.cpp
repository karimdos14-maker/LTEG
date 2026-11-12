#include <GLFW/glfw3.h>
#include <iostream>
#include "LTEG.h"

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(480, 320, "LTEG Engine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    LTEG lteg;
    lteg.engineCycle(window);
    return 0;
}