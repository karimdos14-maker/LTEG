#include <GLFW/glfw3.h>
#include <iostream>
#include "LTEG.h"
#define API 0
#if API == 1
#include "vulkann.h"
#endif
int main(int argc, char **argv)
{
    int width = 800;
    int height = 600;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-width" && i + 1 < argc)
        {
            width = std::stoi(argv[i + 1]);
            i++;
        }
        if (arg == "-height" && i + 1 < argc)
        {
            height = std::stoi(argv[i + 1]);
            i++;
        }
        if (arg == "-api" && i + 1 < argc)
        {
            std::string api_value = argv[i + 1];
            i++;
        }
    }
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(width, height, "LTEG Engine", nullptr, nullptr);
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