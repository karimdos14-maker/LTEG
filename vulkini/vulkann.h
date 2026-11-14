#pragma once
#define GLFW_INCLUDE_VULKAN
#include <Vulkan\vulkan.hpp>
#include <GLFW/glfw3.h>
#include <vector>
class VulkanL
{
private:
    GLFWwindow *window = glfwCreateWindow(800, 600, "LTEG", nullptr, nullptr);
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphics_queue = VK_NULL_HANDLE;
    VkQueue present_queue = VK_NULL_HANDLE;
    VkCommandPool command_pool = VK_NULL_HANDLE;
    VkCommandBuffer command_buffer = VK_NULL_HANDLE;
    vk::Semaphore _imageAvaibleSemaphore;
    vk::Semaphore _renderFinishedSemaphore;
    vk::Fence _inFlightFence;

public:
    bool init_vulkan(GLFWwindow *window);
};