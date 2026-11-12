#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "LTEG.h"
#include "opengl.h"
int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    LTEG lteg;
    lteg.engineCycle(window);
    return 0;
}