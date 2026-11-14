#include <VkBootstrap.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct LTEGContext
{
    vkb::Instance instance;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    vkb::PhysicalDevice physicalDevice;
    vkb::Device device;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;
    uint32_t graphicsFamily = 0;
    uint32_t presentFamily = 0;
};

bool initVulkan(GLFWwindow *window, LTEGContext &ctx)
{
    // instance
    vkb::InstanceBuilder instBuilder;
    auto instRet = instBuilder
                       .set_app_name("LTEG")
                       .set_engine_name("LTEG Engine")
                       .require_api_version(1, 3, 0)
                       .request_validation_layers() // only if the layers are installed
                       .use_default_debug_messenger()
                       .build();
    if (!instRet)
    {
        std::cerr << "Instance error: " << instRet.error().message() << "\n";
        return false;
    }
    ctx.instance = instRet.value();

    // surface
    if (glfwCreateWindowSurface(ctx.instance.instance, window, nullptr, &ctx.surface) != VK_SUCCESS)
    {
        std::cerr << "Failed to create surface\n";
        return false;
    }

    // physical device selection
    VkPhysicalDeviceVulkan13Features features13{};
    features13.dynamicRendering = VK_TRUE;
    features13.synchronization2 = VK_TRUE;

    VkPhysicalDeviceFeatures features10{};
    features10.samplerAnisotropy = VK_TRUE;

    vkb::PhysicalDeviceSelector selector{ctx.instance};
    auto physRet = selector
                       .set_surface(ctx.surface)
                       .set_minimum_version(1, 3)
                       .set_required_features(features10)
                       .set_required_features_13(features13)
                       .prefer_gpu_device_type(vkb::PreferredDeviceType::discrete)
                       .allow_any_gpu_device_type(true) // fall back to integrated if no discrete GPU
                       .select();
    if (!physRet)
    {
        std::cerr << "GPU selection error: " << physRet.error().message() << "\n";
        return false;
    }
    ctx.physicalDevice = physRet.value();
    std::cout << "Selected GPU: " << ctx.physicalDevice.name << "\n";

    // logical device
    vkb::DeviceBuilder deviceBuilder{ctx.physicalDevice};
    auto devRet = deviceBuilder.build();
    if (!devRet)
    {
        std::cerr << "Device error: " << devRet.error().message() << "\n";
        return false;
    }
    ctx.device = devRet.value();

    // queues
    auto gq = ctx.device.get_queue(vkb::QueueType::graphics);
    auto pq = ctx.device.get_queue(vkb::QueueType::present);
    if (!gq || !pq)
    {
        std::cerr << "Failed to get queues\n";
        return false;
    }
    ctx.graphicsQueue = gq.value();
    ctx.presentQueue = pq.value();
    ctx.graphicsFamily = ctx.device.get_queue_index(vkb::QueueType::graphics).value();
    ctx.presentFamily = ctx.device.get_queue_index(vkb::QueueType::present).value();

    return true;
}

void shutdownVulkan(LTEGContext &ctx)
{
    vkb::destroy_device(ctx.device);
    vkb::destroy_surface(ctx.instance, ctx.surface);
    vkb::destroy_instance(ctx.instance);
}