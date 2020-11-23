#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Instance.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

inline auto Get_VkPhysicalDevice(VkInstance instance)
{
    VkPhysicalDevice physical;

    uint32_t count;
    VkPhysicalDevice* physicals;
    VkCheck(vkEnumeratePhysicalDevices(instance, &count, nullptr));
    physicals = new VkPhysicalDevice[count];
    VkCheck(vkEnumeratePhysicalDevices(instance, &count, physicals));
    physical = physicals[0];
    delete[] physicals;
    //com::Print("physicals count", count);
    return physical;
}

///////////////////////////////////////////////////////////

inline auto Get_QueueIndex(VkPhysicalDevice& physical)
{
    uint32_t count;
    VkQueueFamilyProperties* famProps;
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &count, nullptr);
    famProps = new VkQueueFamilyProperties[count];
    vkGetPhysicalDeviceQueueFamilyProperties(physical, &count, famProps);

    uint32_t queueIndex = 0;
    for (uint32_t i = 0; i < count; ++i) 
    {
        if (famProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueIndex = i;
            break;
        }
    }

    //com::Print("queues count", count);
    delete[] famProps;
    return queueIndex;
}

///////////////////////////////////////////////////////////

inline void Print_VK_VERSION(VkPhysicalDeviceProperties& physicalProps)
{
    com::PrintColored(com::ConsoleColor::Cyan, "Vulkan physical API version", 
        VK_VERSION_MAJOR(physicalProps.apiVersion),
        VK_VERSION_MINOR(physicalProps.apiVersion), 
        VK_VERSION_PATCH(physicalProps.apiVersion)
    );
}

///////////////////////////////////////////////////////////

inline void Print_VkPhysicalDeviceProperties(VkPhysicalDeviceProperties& physicalProps)
{
    com::Print(com::ConsoleColor::Yellow, "device");
    com::Print("deviceName", physicalProps.deviceName);
    com::Print("deviceType", physicalProps.deviceType);
    com::Print("driverVersion", physicalProps.driverVersion);
    com::Print("vendorID", physicalProps.vendorID);

    com::Print(com::ConsoleColor::Yellow, "limits");
    auto& limits = physicalProps.limits;
    com::Print("maxBoundDescriptorSets", limits.maxBoundDescriptorSets);
    com::Print("maxColorAttachments", limits.maxColorAttachments);
    com::Print("maxDrawIndexedIndexValue", limits.maxDrawIndexedIndexValue);
    com::Print("maxFramebufferWidth", limits.maxFramebufferWidth);
    com::Print("maxFramebufferHeight", limits.maxFramebufferHeight);
    com::Print(com::ConsoleColor::Magenta, "maxImageArrayLayers", limits.maxImageArrayLayers);
    com::Print("maxImageDimension2D", limits.maxImageDimension2D);
    com::Print("maxMemoryAllocationCount", limits.maxMemoryAllocationCount);
    com::Print(com::ConsoleColor::Magenta, "maxPushConstantsSize", limits.maxPushConstantsSize);
    com::Print("maxStorageBufferRange", limits.maxStorageBufferRange);
    com::Print("maxUniformBufferRange", limits.maxUniformBufferRange);
    com::Print("minMemoryMapAlignment", limits.minMemoryMapAlignment);
}

////////////////////////////////////////////////////////////

inline void Print_VkPhysicalDeviceFeatures(VkPhysicalDevice& physical)
{
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(physical, &features);
    com::Print(com::ConsoleColor::Yellow, "device features");
    com::PrintBool(features.wideLines, "wideLines");
    com::PrintBool(features.shaderInt16, "shaderInt16");
    com::PrintBool(features.largePoints, "largePoints");
    com::PrintBool(features.geometryShader, "geometryShader");
    com::PrintBool(features.alphaToOne, "alphaToOne");
}

///////////////////////////////////////////////////////////

inline void Print_VkPhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties& memoryProps)
{
    com::Print(com::ConsoleColor::Yellow, "memory");
    com::Print("memoryHeapCount", memoryProps.memoryHeapCount);
    com::Print("memoryTypeCount", memoryProps.memoryTypeCount);
}

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
    physical   = Get_VkPhysicalDevice(instance.instance);
    queueIndex = Get_QueueIndex(physical);

    vkGetPhysicalDeviceProperties(physical, &physicalProps);
    vkGetPhysicalDeviceMemoryProperties(physical, &memoryProps);

    Print_VK_VERSION(physicalProps);
    //Print_VkPhysicalDeviceProperties(physicalProps);
    //Print_VkPhysicalDeviceMemoryProperties(memoryProps);
    //Print_VkPhysicalDeviceFeatures(physical);
}

///////////////////////////////////////////////////////////

};
}//ns