#include "vulkann.h"

int VulkanL::vulkan_initiliaze_vkInstance()
{
    VkInstance instance;
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "LTEG";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 1, 0);
    appInfo.pEngineName = "LTEG engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_3;
}