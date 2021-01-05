#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Context/Context.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline u32 MemoryType(
VkMemoryRequirements& memReqs,
VkMemoryPropertyFlags neededMemProps) 
{
    auto& physicalMemProps = g_contextPtr->physical.memoryProps;
    for (uint32_t i = 0; i < physicalMemProps.memoryTypeCount; ++i) {
        if (memReqs.memoryTypeBits & (1 << i) &&
            (physicalMemProps.memoryTypes[i].propertyFlags & neededMemProps) == neededMemProps) 
            return i;
    }
    com::PrintError("no suitable memory type found!");
    return {};
}

///////////////////////////////////////////////////////////

inline auto AllocationInfo(VkMemoryRequirements& memReqs, VkMemoryPropertyFlags memProps)
{
    return VkMemoryAllocateInfo
    {
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext           = nullptr,
        .allocationSize  = memReqs.size,
        .memoryTypeIndex = MemoryType(memReqs, memProps)
    };
}

///////////////////////////////////////////////////////////

template<typename T>
inline auto AllocateMemory(T& imageOrBuffer, VkDeviceMemory& memory, VkMemoryPropertyFlags memProps)
{
    constexpr auto isBuffer = std::is_same_v<T, VkBuffer>;
    VkMemoryRequirements memReqs;

    if constexpr(isBuffer)
    vkGetBufferMemoryRequirements(g_devicePtr, imageOrBuffer, &memReqs);
    else
    vkGetImageMemoryRequirements(g_devicePtr, imageOrBuffer, &memReqs);   

    auto allocInfo = AllocationInfo(memReqs, memProps);
    VkCheck(vkAllocateMemory(g_devicePtr, &allocInfo, nullptr, &memory));   

    if constexpr(isBuffer)
    VkCheck(vkBindBufferMemory(g_devicePtr, imageOrBuffer, memory, 0));
    else
    VkCheck(vkBindImageMemory(g_devicePtr, imageOrBuffer, memory, 0));
}

///////////////////////////////////////////////////////////

inline void PrintPhysicalAPI()
{
    auto& physicalProps = g_contextPtr->physical.physicalProps;
    com::PrintColored(com::ConsoleColor::Magenta, "Vulkan physical API version", 
        VK_VERSION_MAJOR(physicalProps.apiVersion),
        VK_VERSION_MINOR(physicalProps.apiVersion), 
        VK_VERSION_PATCH(physicalProps.apiVersion)
    );
}

///////////////////////////////////////////////////////////

inline void PrintPhysical()
{
    auto& physical = g_contextPtr->physical.physical;
    auto& physicalProps = g_contextPtr->physical.physicalProps;
    auto& memoryProps = g_contextPtr->physical.memoryProps;

    com::Print(com::ConsoleColor::Yellow, "device");
    com::Print("deviceName", physicalProps.deviceName);
    com::Print("deviceType", physicalProps.deviceType);
    com::Print("driverVersion", physicalProps.driverVersion);
    com::Print("vendorID", physicalProps.vendorID);

    auto& limits = physicalProps.limits;
    com::Print(com::ConsoleColor::Yellow, "limits");
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

    com::Print(com::ConsoleColor::Yellow, "memory");
    com::Print("memoryHeapCount", memoryProps.memoryHeapCount);
    com::Print("memoryTypeCount", memoryProps.memoryTypeCount);

    com::Print(com::ConsoleColor::Yellow, "features");
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

}//ns