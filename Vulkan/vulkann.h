#pragma once
#include <Vulkan\vulkan.hpp>
class VulkanL
{
public:
    VkInstance _instance = VK_NULL_HANDLE;
    VkDevice _device = VK_NULL_HANDLE;
    VkPhysicalDevice _chosenGPU = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT _debug_messenger = VK_NULL_HANDLE;
    VkSurfaceKHR _window = VK_NULL_HANDLE;

private:
    bool init_vulkan_surface();
    bool init_vulkan_VkInstance();
    bool init_vulkan_device();
    bool init_vulkan_phys_device();
    bool init_swapchain();
};