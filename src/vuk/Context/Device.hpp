#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Physical.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {
struct Device {

////////////////////////////////////////////////////////////

VkDevice device;
VkQueue  queue;

///////////////////////////////////////////////////////////

void Create(Physical& physical)
{
    float priorities { 1.f };
    VkDeviceQueueCreateInfo const queueInfo
    {
        .sType             = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext             = nullptr,
        .flags             = 0,
        .queueFamilyIndex  = physical.queueIndex,
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

    VkCheck(vkCreateDevice(physical.physical, &deviceInfo, nullptr, &device));
    vkGetDeviceQueue(device, physical.queueIndex, 0, &queue);

    g_devicePtr = device;
}

///////////////////////////////////////////////////////////

void Destroy()
{
    vkDestroyDevice(device, nullptr);
    g_devicePtr = nullptr;
}

///////////////////////////////////////////////////////////

};
}//ns