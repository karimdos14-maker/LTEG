#include <VkBootstrap.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

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
    vkb::Swapchain swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    VkCommandPool commandPool = VK_NULL_HANDLE;
    VkCommandBuffer mainCommandBuffer = VK_NULL_HANDLE;

    VkSemaphore swapchainSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderSemaphore = VK_NULL_HANDLE;
    VkFence renderFence = VK_NULL_HANDLE;
};

bool createSwapchain(GLFWwindow *window, LTEGContext &ctx)
{
    int w = 0, h = 0;
    glfwGetFramebufferSize(window, &w, &h);

    vkb::SwapchainBuilder builder{ctx.device};
    auto swapRet = builder
                       .set_desired_format({VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
                       .set_desired_present_mode(VK_PRESENT_MODE_MAILBOX_KHR) // falls back to FIFO
                       .add_fallback_present_mode(VK_PRESENT_MODE_FIFO_KHR)
                       .set_desired_extent(static_cast<uint32_t>(w), static_cast<uint32_t>(h))
                       .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
                       .set_old_swapchain(ctx.swapchain)
                       .build();
    if (!swapRet)
    {
        std::cerr << "Swapchain error: " << swapRet.error().message() << "\n";
        return false;
    }

    if (ctx.swapchain.swapchain != VK_NULL_HANDLE)
    {
        ctx.swapchain.destroy_image_views(ctx.swapchainImageViews);
        vkb::destroy_swapchain(ctx.swapchain);
    }

    ctx.swapchain = swapRet.value();
    ctx.swapchainImages = ctx.swapchain.get_images().value();
    ctx.swapchainImageViews = ctx.swapchain.get_image_views().value();
    return true;
}

bool initVulkan(GLFWwindow *window, LTEGContext &ctx)
{

    vkb::InstanceBuilder instBuilder;
    auto instRet = instBuilder
                       .set_app_name("LTEG")
                       .set_engine_name("LTEG Engine")
                       .require_api_version(1, 3, 0)
                       .use_default_debug_messenger()
                       .build();
    if (!instRet)
    {
        std::cerr << "Instance error: " << instRet.error().message() << "\n";
        return false;
    }
    ctx.instance = instRet.value();

    if (glfwCreateWindowSurface(ctx.instance.instance, window, nullptr, &ctx.surface) != VK_SUCCESS)
    {
        std::cerr << "Failed to create surface\n";
        return false;
    }

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

    vkb::DeviceBuilder deviceBuilder{ctx.physicalDevice};
    auto devRet = deviceBuilder.build();
    if (!devRet)
    {
        std::cerr << "Device error: " << devRet.error().message() << "\n";
        return false;
    }
    ctx.device = devRet.value();

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

    if (!createSwapchain(window, ctx))
        return false;

    return true;
}
bool initCommandsAndSync(LTEGContext &ctx)
{
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = ctx.graphicsFamily;

    if (vkCreateCommandPool(ctx.device.device, &poolInfo, nullptr, &ctx.commandPool) != VK_SUCCESS)
    {
        std::cerr << "Failed to create command pool\n";
        return false;
    }

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = ctx.commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(ctx.device.device, &allocInfo, &ctx.mainCommandBuffer) != VK_SUCCESS)
    {
        std::cerr << "Failed to allocate command buffer\n";
        return false;
    }

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    VkSemaphoreCreateInfo semInfo{};
    semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateFence(ctx.device.device, &fenceInfo, nullptr, &ctx.renderFence) != VK_SUCCESS ||
        vkCreateSemaphore(ctx.device.device, &semInfo, nullptr, &ctx.swapchainSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(ctx.device.device, &semInfo, nullptr, &ctx.renderSemaphore) != VK_SUCCESS)
    {
        std::cerr << "Failed to create sync objects\n";
        return false;
    }

    return true;
}

void transitionImage(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout)
{
    VkImageMemoryBarrier2 imageBarrier{};
    imageBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
    imageBarrier.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    imageBarrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
    imageBarrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    imageBarrier.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT;

    imageBarrier.oldLayout = currentLayout;
    imageBarrier.newLayout = newLayout;
    imageBarrier.image = image;
    imageBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageBarrier.subresourceRange.baseMipLevel = 0;
    imageBarrier.subresourceRange.levelCount = 1;
    imageBarrier.subresourceRange.baseArrayLayer = 0;
    imageBarrier.subresourceRange.layerCount = 1;

    VkDependencyInfo depInfo{};
    depInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
    depInfo.imageMemoryBarrierCount = 1;
    depInfo.pImageMemoryBarriers = &imageBarrier;

    vkCmdPipelineBarrier2(cmd, &depInfo);
}

void drawFrame(LTEGContext &ctx)
{
    vkWaitForFences(ctx.device.device, 1, &ctx.renderFence, VK_TRUE, 1000000000);
    vkResetFences(ctx.device.device, 1, &ctx.renderFence);

    uint32_t swapchainImageIndex;
    vkAcquireNextImageKHR(ctx.device.device, ctx.swapchain.swapchain, 1000000000, ctx.swapchainSemaphore, VK_NULL_HANDLE, &swapchainImageIndex);

    VkImage currentImage = ctx.swapchainImages[swapchainImageIndex];

    VkCommandBuffer cmd = ctx.mainCommandBuffer;
    vkResetCommandBuffer(cmd, 0);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cmd, &beginInfo);

    transitionImage(cmd, currentImage, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    VkClearColorValue clearValue = {{0.1f, 0.2f, 0.4f, 1.0f}};
    VkImageSubresourceRange clearRange{};
    clearRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    clearRange.levelCount = 1;
    clearRange.layerCount = 1;

    vkCmdClearColorImage(cmd, currentImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearValue, 1, &clearRange);

    transitionImage(cmd, currentImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

    vkEndCommandBuffer(cmd);

    VkCommandBufferSubmitInfo cmdSubmitInfo{};
    cmdSubmitInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO;
    cmdSubmitInfo.commandBuffer = cmd;

    VkSemaphoreSubmitInfo waitInfo{};
    waitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    waitInfo.semaphore = ctx.swapchainSemaphore;
    waitInfo.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSemaphoreSubmitInfo signalInfo{};
    signalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
    signalInfo.semaphore = ctx.renderSemaphore;
    signalInfo.stageMask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT;

    VkSubmitInfo2 submit{};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2;
    submit.waitSemaphoreInfoCount = 1;
    submit.pWaitSemaphoreInfos = &waitInfo;
    submit.signalSemaphoreInfoCount = 1;
    submit.pSignalSemaphoreInfos = &signalInfo;
    submit.commandBufferInfoCount = 1;
    submit.pCommandBufferInfos = &cmdSubmitInfo;

    vkQueueSubmit2(ctx.graphicsQueue, 1, &submit, ctx.renderFence);

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pSwapchains = &ctx.swapchain.swapchain;
    presentInfo.swapchainCount = 1;
    presentInfo.pWaitSemaphores = &ctx.renderSemaphore;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pImageIndices = &swapchainImageIndex;

    vkQueuePresentKHR(ctx.presentQueue, &presentInfo);
}
void shutdownVulkan(LTEGContext &ctx)
{
    vkDeviceWaitIdle(ctx.device.device);

    ctx.swapchain.destroy_image_views(ctx.swapchainImageViews);
    vkb::destroy_swapchain(ctx.swapchain);

    vkb::destroy_device(ctx.device);
    vkb::destroy_surface(ctx.instance, ctx.surface);
    vkb::destroy_instance(ctx.instance);
}
