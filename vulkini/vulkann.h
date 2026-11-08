#pragma once
#define GLFW_INCLUDE_VULKAN
#include <Vulkan\vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
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
    std::vector<vk::Image> _swapchainImages;
    std::vector<vk::ImageView> _swapchainImageViews;
    vk::SwapchainKHR _swapchain{};
    uint32_t _graphicsFamily = 0;
    vk::Format _swapchainImageFormat{};
    uint32_t _presentFamily = 0;
    vk::Extent2D _swapchainExtent;
    uint32_t _currentImageIndex = 0;
    vk::CommandPool _commandPool;
    vk::CommandBuffer _commandBuffer;
    // Func

    bool init_vulkan_VkInstance();
    bool init_vulkan_surface(GLFWwindow *window);
    bool init_vulkan_device();
    bool init_vulkan_phys_device();
    bool init_swapchain();
    bool init_image_views();
    bool init_dynamic_rendering();
};