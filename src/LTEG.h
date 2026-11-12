#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class LTEG
{
private:
public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
};
