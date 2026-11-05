#include "vulkann.h"
class VulkanL
{
public:
    VkInstance _instance;
    VkDevice _device;
    VkPhysicalDevice _chosenGPU;
    VkDebugUtilsMessengerEXT _debug_messenger;
    VkSurfaceKHR _window;
};