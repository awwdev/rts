#pragma once

#include "vuk/Vulkan.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

static void CreatePhysical(
VkInstance instance, 
VkPhysicalDevice& physical, 
uint32_t& queueIndex,
VkPhysicalDeviceProperties& physicalProps,
VkPhysicalDeviceMemoryProperties& memoryProps)
{
    {
        uint32_t count;
        VkPhysicalDevice* physicals;
        VkCheck(vkEnumeratePhysicalDevices(instance, &count, nullptr));
        physicals = new VkPhysicalDevice[count];
        VkCheck(vkEnumeratePhysicalDevices(instance, &count, physicals));
        physical = physicals[0]; //!
        delete[] physicals;
    }

    {
        uint32_t count;
        VkQueueFamilyProperties* famProps;
        vkGetPhysicalDeviceQueueFamilyProperties(physical, &count, nullptr);
        famProps = new VkQueueFamilyProperties[count];
        vkGetPhysicalDeviceQueueFamilyProperties(physical, &count, famProps);

        for (uint32_t i = 0; i < count; ++i) 
        {
            if (famProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                queueIndex = i;
                break;
            }
        }

        delete[] famProps;
    }

    vkGetPhysicalDeviceProperties(physical, &physicalProps);
    vkGetPhysicalDeviceMemoryProperties(physical, &memoryProps);

    com::PrintColored(com::ConsoleColor::Cyan, "Vulkan physical API version", 
        VK_VERSION_MAJOR(physicalProps.apiVersion),
        VK_VERSION_MINOR(physicalProps.apiVersion), 
        VK_VERSION_PATCH(physicalProps.apiVersion)
    );
}

///////////////////////////////////////////////////////////

}//ns