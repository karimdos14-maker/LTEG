#pragma once
#include "vulkann.h"
#include <GLFW/glfw3.h>
class LTEG
{
private:
    VulkanL _vulkan;

public:
    int engineCycle(GLFWwindow *window);
    void generateChunk();
    void deleteChunk();
    void addObject();
};