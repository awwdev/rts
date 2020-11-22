#pragma once

#include "vuk/Vulkan.hpp"

#include "vuk/Context/Instance.hpp"
#include "vuk/Context/Physical.hpp"
#include "vuk/Context/Device.hpp"
#include "vuk/Context/Surface.hpp"
#include "vuk/Context/Swapchain.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {
struct Context {

///////////////////////////////////////////////////////////

VkInstance instance;
VkPhysicalDevice physical;
uint32_t queueIndex;
VkDevice device;
VkSurfaceKHR surface;
VkSwapchainKHR swapchain;
VkDebugUtilsMessengerEXT debugMessenger;
VkPhysicalDeviceProperties physicalProps;
VkPhysicalDeviceMemoryProperties memoryProps;

///////////////////////////////////////////////////////////

Context()
{
    CreateInstance  (instance, debugMessenger, VK_API_VERSION_1_0);
    CreatePhysical  (instance, physical, queueIndex, physicalProps, memoryProps);
    CreateDevice    (device);
    CreateSurface   (surface);
    CreateSwapchain (swapchain);
}

///////////////////////////////////////////////////////////

~Context()
{
    DestroySwapchain(swapchain);
    DestroySurface(surface);
    DestroyDevice(device);
    DestroyInstance(instance);
}

///////////////////////////////////////////////////////////

};
}//ns