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
VkQueue queue;
VkDevice device;
VkSurfaceKHR surface;
VkSwapchainKHR swapchain;
VkDebugUtilsMessengerEXT debugMessenger;
VkPhysicalDeviceProperties physicalProps;
VkPhysicalDeviceMemoryProperties memoryProps;
VkSurfaceCapabilitiesKHR surfaceCapabilities;

uint32_t swapImagesCount;
VkImage* swapImages;
uint32_t swapImageViewsCount;
VkImageView* swapImageViews;

///////////////////////////////////////////////////////////

Context(WindowHandle const& wndHandle)
{
    CreateInstance  (instance, debugMessenger, VK_API_VERSION_1_0);
    CreatePhysical  (instance, physical, queueIndex, physicalProps, memoryProps);
    CreateDevice    (device, queueIndex, physical, queue);
    CreateSurface   (surface, instance, physical, queueIndex, surfaceCapabilities, wndHandle);
    CreateSwapchain (device, surface, swapchain, surfaceCapabilities, 
    swapImages, swapImagesCount, swapImageViews, swapImageViewsCount,
    VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR, VK_PRESENT_MODE_FIFO_KHR);
    //VK_PRESENT_MODE_IMMEDIATE_KHR
}

///////////////////////////////////////////////////////////

~Context()
{
    DestroySwapchain(device, swapchain, swapImageViews, swapImageViewsCount, swapImages);
    DestroySurface  (instance, surface);
    DestroyDevice   (device);
    DestroyInstance (instance, debugMessenger);
    g_devicePtr = nullptr;
}

///////////////////////////////////////////////////////////

};
}//ns