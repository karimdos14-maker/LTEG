#pragma once
#include <GLFW/glfw3.h>
class LTEG
{
private:
    GLFWwindow *window;
    int objposition[3] = {0, 0, 0};

public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
    bool objectposition();
};
