#pragma once

#include "vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

static void CreateDevice(VkDevice& device, uint32_t queueIndex, VkPhysicalDevice& physical, VkQueue& queue)
{
    float priorities { 1.f };
    VkDeviceQueueCreateInfo const queueInfo
    {
        .sType             = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext             = nullptr,
        .flags             = 0,
        .queueFamilyIndex  = queueIndex,
        .queueCount        = 1,
        .pQueuePriorities  = &priorities
    };

    chars_t physicalExtensions[] 
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkPhysicalDeviceFeatures deviceFeatures {};

    VkDeviceCreateInfo const deviceInfo 
    {
        .sType                      = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext                      = nullptr,
        .flags                      = 0,
        .queueCreateInfoCount       = 1,
        .pQueueCreateInfos          = &queueInfo,
        .enabledLayerCount          = 0,
        .ppEnabledLayerNames        = nullptr,
        .enabledExtensionCount      = array_extent(physicalExtensions),
        .ppEnabledExtensionNames    = physicalExtensions,
        .pEnabledFeatures           = &deviceFeatures
    };

    VkCheck(vkCreateDevice(physical, &deviceInfo, nullptr, &device));
    vkGetDeviceQueue(device, queueIndex, 0, &queue);

    g_devicePtr = device;
}

///////////////////////////////////////////////////////////

static void DestroyDevice(VkDevice device)
{
    vkDestroyDevice(device, nullptr);
}

///////////////////////////////////////////////////////////

}//ns