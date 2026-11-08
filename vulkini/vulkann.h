#pragma once
#define GLFW_INCLUDE_VULKAN
#include <Vulkan\vulkan.hpp>
#include <GLFW/glfw3.h>
class VulkanL
{
private:
public:
    // Handle
    vk::Instance _instance = nullptr;
    vk::Device _device = nullptr;
    vk::PhysicalDevice _chosenGPU = nullptr;
    vk::DebugUtilsMessengerEXT _debug_messenger = nullptr;
    vk::SurfaceKHR _window = nullptr;
    vk::Queue _graphicsQueue;
    vk::Queue _presentQueue;
    uint32_t _graphicsFamily = 0;
    uint32_t _presentFamily = 0;
    // Func

    bool init_vulkan_VkInstance();
    bool init_vulkan_surface(GLFWwindow *window);
    bool init_vulkan_device();
    bool init_vulkan_phys_device();
    bool init_swapchain();
};