#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Instance.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Physical {

///////////////////////////////////////////////////////////

VkPhysicalDevice physical;
VkPhysicalDeviceProperties physicalProps;
VkPhysicalDeviceMemoryProperties memoryProps;
uint32_t queueIndex;

////////////////////////////////////////////////////////////

void Create(Instance& instance)
{
    uint32_t physicalsCount;
    VkPhysicalDevice* physicals;
    VkCheck(vkEnumeratePhysicalDevices(instance.instance, &physicalsCount, nullptr));
    physicals = new VkPhysicalDevice[physicalsCount];
    VkCheck(vkEnumeratePhysicalDevices(instance.instance, &physicalsCount, physicals));
    physical = physicals[0];
    delete[] physicals;

    uint32_t famPropsCount;
    VkQueueFamilyProperties* famProps;
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &famPropsCount, nullptr);
    famProps = new VkQueueFamilyProperties[famPropsCount];
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &famPropsCount, famProps);
    for (uint32_t i = 0; i < famPropsCount; ++i) 
    {
        if (famProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueIndex = i;
            break;
        }
    }
    //com::Print("queues count", count);
    delete[] famProps;

    vkGetPhysicalDeviceProperties(physical, &physicalProps);
    vkGetPhysicalDeviceMemoryProperties(physical, &memoryProps);
}

///////////////////////////////////////////////////////////

};

///////////////////////////////////////////////////////////

}//ns