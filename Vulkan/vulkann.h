#pragma once
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
class VulkanL
{
public:
    int run_app();
    int vulkan_initiliaze_VkInstance();
    int vulkan_initiliaze_VkPhysDevice();
};
