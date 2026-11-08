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
    vk::PhysicalDeviceVulkan13Features features13{};
    features13.dynamicRendering = VK_TRUE;

    deviceCreateInfo.pNext = &features13;
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
bool VulkanL::init_swapchain()
{
    vk::SurfaceCapabilitiesKHR capabilities = _chosenGPU.getSurfaceCapabilitiesKHR(_window);
    auto formats =
        _chosenGPU.getSurfaceFormatsKHR(_window);
    auto presentModes =
        _chosenGPU.getSurfacePresentModesKHR(_window);

    vk::SurfaceFormatKHR surfaceFormat = formats[0];
    _swapchainImageFormat = surfaceFormat.format;
    vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;

    vk::Extent2D extent = capabilities.currentExtent;

    uint32_t imageCount = capabilities.minImageCount + 1;

    vk::SwapchainCreateInfoKHR createInfo{};
    createInfo.surface = _window;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
    createInfo.imageSharingMode = vk::SharingMode::eExclusive;
    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    _swapchain = _device.createSwapchainKHR(createInfo);
    return true;
};
bool VulkanL::init_image_views()
{
    _swapchainImages = _device.getSwapchainImagesKHR(_swapchain);

    _swapchainImageViews.clear();
    _swapchainImageViews.reserve(_swapchainImages.size());

    for (const auto &image : _swapchainImages)
    {
        vk::ImageViewCreateInfo createInfo{};

        createInfo.image = image;
        createInfo.viewType = vk::ImageViewType::e2D;
        createInfo.format = _swapchainImageFormat;

        createInfo.subresourceRange.aspectMask =
            vk::ImageAspectFlagBits::eColor;

        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        _swapchainImageViews.push_back(
            _device.createImageView(createInfo));
    }

    std::cout << "Image Views created: "
              << _swapchainImageViews.size() << '\n';

    return true;
}

bool VulkanL::init_dynamic_rendering()
{
    if (_swapchainImageViews.empty())
    {
        return false;
    }

    vk::RenderingAttachmentInfo colorAttachment{};
    colorAttachment.imageView = _swapchainImageViews[_currentImageIndex];
    colorAttachment.imageLayout = vk::ImageLayout::eColorAttachmentOptimal;
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachment.clearValue = vk::ClearValue{std::array<float, 4>{0.1f, 0.1f, 0.1f, 1.0f}};

    vk::RenderingInfo renderingInfo{};
    renderingInfo.renderArea = vk::Rect2D{{0, 0}, _swapchainExtent};
    renderingInfo.layerCount = 1;
    renderingInfo.colorAttachmentCount = 1;
    renderingInfo.pColorAttachments = &colorAttachment;

    _commandBuffer.begin(vk::CommandBufferBeginInfo{});

    _commandBuffer.beginRendering(renderingInfo);

    _commandBuffer.endRendering();
    _commandBuffer.end();

    return true;
}