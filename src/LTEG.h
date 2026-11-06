#pragma once
#include "vulkann.h"
class LTEG
{
private:
    VulkanL _vulkan;

public:
    int engineCycle();
    void generateChunk();
    void deleteChunk();
    void addObject();
};