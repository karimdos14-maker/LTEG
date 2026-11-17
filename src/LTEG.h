#pragma once
#include <GLFW/glfw3.h>
#include <memory>
class LTEG
{
private:
    GLFWwindow *window;

public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
    bool objectposition();
};
