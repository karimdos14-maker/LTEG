#include "vulkann.h"
#include <iostream>
bool VulkanL::init_vulkan_VkInstance()
{
    try
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtension = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        vk::ApplicationInfo appInfo{};
        appInfo.pApplicationName = "LTEG ";
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
        appInfo.pEngineName = "LTEG Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 1);
        appInfo.apiVersion = VK_API_VERSION_1_3;
        vk::InstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtension;
        _instance = vk::createInstance(createInfo);
        std::cout << "Success\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error Vulkan INI" << e.what() << '\n';
        return false;
    }
}