#pragma once
#include <Vulkan\vulkan.hpp>
#include <GLFW/glfw3.h>
class VulkanL
{
public:
    // Handle
    vk::Instance _instance = nullptr;
    vk::Device _device = nullptr;
    vk::PhysicalDevice _chosenGPU = nullptr;
    vk::DebugUtilsMessengerEXT _debug_messenger = nullptr;
    vk::SurfaceKHR _window = nullptr;
    // Func
    bool init_vulkan_surface();
    bool init_vulkan_VkInstance();
    bool init_vulkan_device();
    bool init_vulkan_phys_device();
    bool init_swapchain();
};