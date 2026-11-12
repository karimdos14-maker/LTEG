#pragma once
#include <GLFW/glfw3.h>
class LTEG
{
private:
    GLFWwindow *window;

public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
};
