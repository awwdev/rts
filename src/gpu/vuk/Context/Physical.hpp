#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Context/Instance.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct Physical 
{
    VkPhysicalDevice physical;
    VkPhysicalDeviceProperties physicalProps;
    VkPhysicalDeviceMemoryProperties memoryProps;
    uint32_t queueIndex;

    void Create(Instance&);
};

///////////////////////////////////////////////////////////

void Physical::Create(Instance& instance)
{
    com::POD_Array<VkPhysicalDevice, 10> physicals;
    VkCheck(vkEnumeratePhysicalDevices(instance.instance, &physicals.count, nullptr));
    VkCheck(vkEnumeratePhysicalDevices(instance.instance, &physicals.count, physicals.data));
    physical = physicals[0];

    com::POD_Array<VkQueueFamilyProperties, 10> famProps;
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &famProps.count, nullptr);
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &famProps.count, famProps.data);
    FOR_ARRAY(famProps, i)
    {
        if (famProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueIndex = i;
            break;
        }
    }
    //com::Print("queues count", count);

    vkGetPhysicalDeviceProperties(physical, &physicalProps);
    vkGetPhysicalDeviceMemoryProperties(physical, &memoryProps);
}

///////////////////////////////////////////////////////////

}//ns