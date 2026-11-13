#include "VkBootstrap.h"
#include "vulkann.h"
#include <iostream>
#include <GLFW/glfw3.h>
bool VulkanL::init_vulkan(GLFWwindow *window)
{
    // instance
    vkb::InstanceBuilder inBuilder;
    auto instance_res = inBuilder.set_app_name("LTEG Engine")
                            .request_validation_layers(true)
                            .use_default_debug_messenger()
                            .require_api_version(1, 3, 0)
                            .build();

    if (!instance_res)
    {
        std::cout << "Instance dont created! Error: " << instance_res.error().message() << "\n";
        return false;
    }

    vkb::Instance vkb_instance = instance_res.value();
    VkInstance instance = vkb_instance.instance;

    window = glfwCreateWindow(800, 600, "LTEG Engine", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window!\n";
        return false;
    }

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
    {
        std::cout << "Failed to create window surface!\n";
        return false;
    }
    // Physdevice
    vkb::PhysicalDeviceSelector selector(vkb_instance);
    auto phys_ret = selector.set_surface(surface)
                        .set_minimum_version(1, 3)
                        .add_required_extension(VK_KHR_SWAPCHAIN_EXTENSION_NAME)
                        .select();

    if (!phys_ret)
    {
        std::cout << "Failed to select Vulkan physical device: " << phys_ret.error().message() << "\n";
        return false;
    }
    vkb::PhysicalDevice vkb_physical_device = phys_ret.value();
    physical_device = vkb_physical_device.physical_device;

    vkb::DeviceBuilder device_builder(vkb_physical_device);
    auto dev_ret = device_builder.build();
    if (!dev_ret)
    {
        std::cout << "Failed to create logical device: " << dev_ret.error().message() << "\n";
        return false;
    }
    // device
    vkb::Device vkb_device = dev_ret.value();
    device = vkb_device.device;
    // swapchain

    // vkqueue
    VkQueue graph_queue = vkb_device.get_queue(vkb::QueueType::graphics).value();
    VkQueue presnt_queue = vkb_device.get_queue(vkb::QueueType::present).value();
    // graph queue
    auto g_queue_ret = vkb_device.get_queue(vkb::QueueType::graphics);
    if (!g_queue_ret)
    {
        std::cout << "Failed to get graphics queue: " << g_queue_ret.error().message() << "\n";
        return false;
    }
    graphics_queue = g_queue_ret.value();

    auto p_queue_ret = vkb_device.get_queue(vkb::QueueType::present);
    if (!p_queue_ret)
    {
        std::cout << "Failed to get present queue: " << p_queue_ret.error().message() << "\n";
        return false;
    }
    present_queue = p_queue_ret.value();
    vkb::SwapchainBuilder swapchain_builder(vkb_device);
    auto swap_ret = swapchain_builder
                        .set_desired_format({VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
                        .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
                        .set_desired_extent(800, 600)
                        .build();

    if (!swap_ret)
    {
        std::cout << "Failed to create Vulkan swapchain: " << swap_ret.error().message() << "\n";
        return false;
    }

    vkb::Swapchain vkb_swapchain = swap_ret.value();
    VkSwapchainKHR swapchain = vkb_swapchain.swapchain;

    std::vector<VkImage> swapchain_images = vkb_swapchain.get_images().value();
    std::vector<VkImageView> swapchain_image_views = vkb_swapchain.get_image_views().value();
    VkFormat swapchain_image_format = vkb_swapchain.image_format;
    VkExtent2D swapchain_extent = vkb_swapchain.extent;
    // command pool
    auto graphics_queue_index_opt = vkb_device.get_queue_index(vkb::QueueType::graphics);
    if (!graphics_queue_index_opt)
    {
        std::cout << "Failed to get graphics queue index\n";
        return false;
    }
    uint32_t graphics_queue_index = graphics_queue_index_opt.value();

    VkCommandPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pool_info.queueFamilyIndex = graphics_queue_index;

    if (vkCreateCommandPool(device, &pool_info, nullptr, &command_pool) != VK_SUCCESS)
    {
        std::cout << "Failed to create command pool!\n";
        return false;
    }

    VkCommandBufferAllocateInfo alloc_info = {};
    alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    alloc_info.commandPool = command_pool;
    alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    alloc_info.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(device, &alloc_info, &command_buffer) != VK_SUCCESS)
    {
        std::cout << "Failed to allocate command buffer!\n";
        return false;
    }
}