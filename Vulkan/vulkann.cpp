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

        uint32_t count;
        const char **extension = glfwGetRequiredInstanceExtensions(&count);

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
bool VulkanL::init_vulkan_surface(GLFWwindow *window)
{
    if (!glfwVulkanSupported())
    {
        std::cerr << "Vulkan dont work\n";
        return false;
    }

    VkSurfaceKHR c_surface;

    VkResult result = glfwCreateWindowSurface(
        static_cast<VkInstance>(_instance),
        window,
        nullptr,
        &c_surface);

    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to create window surface!\n";
        return false;
    }

    _window = vk::SurfaceKHR(c_surface);
    std::cout << "Surface created!\n";
    return true;
}
bool VulkanL::init_vulkan_phys_device()
{
    std::vector<vk::PhysicalDevice> devices = _instance.enumeratePhysicalDevices();
    if (devices.empty())
    {
        std::cerr << "Failed" << std::endl;
        return false;
    }

    _chosenGPU = devices[0];

    vk::PhysicalDeviceProperties props = _chosenGPU.getProperties();
    std::cout << "Selected GPU: " << props.deviceName << std::endl;

    return true;
}
bool VulkanL::init_vulkan_device()
{

    auto queueFamilies = _chosenGPU.getQueueFamilyProperties();

    for (uint32_t i = 0; i < queueFamilies.size(); i++)
    {

        if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
        {
            _graphicsFamily = i;
        }

        if (_chosenGPU.getSurfaceSupportKHR(i, _window))
        {
            _presentFamily = i;
        }
    }

    float queuePriority = 1.0f;
    vk::DeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.queueFamilyIndex = _graphicsFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    vk::DeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

    try
    {
        _device = _chosenGPU.createDevice(deviceCreateInfo);
    }
    catch (const vk::SystemError &err)
    {
        std::cerr << "Failed to create logical device: " << err.what() << std::endl;
        return false;
    }

    _graphicsQueue = _device.getQueue(_graphicsFamily, 0);
    _presentQueue = _device.getQueue(_presentFamily, 0);

    std::cout << "Logial and queues created" << std::endl;
    return true;
}
