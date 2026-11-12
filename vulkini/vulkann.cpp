#include "VkBootstrap.h"
#include "vulkann.h"
#include <iostream>
bool VulkanL::init_vulkan()
{
    vkb::InstanceBuilder inBuilder;
    auto instance_res = inBuilder.set_app_name("LTEG Engine")
                            .request_validation_layers()
                            .use_default_debug_messenger()
                            .build();
    if (!instance_res)
    {
        std::cout << "Instance dont created!\n";
    };
    VkInstance instance = instance_res.value();

    vkb::PhysicalDeviceSelector selector(vkb::Instance);
}
