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
VkDevice device;
VkSurfaceKHR surface;
VkSwapchainKHR swapchain;

///////////////////////////////////////////////////////////

Context()
{
    CreateInstance(instance);
    CreatePhysical(physical);
    CreateDevice(device);
    CreateSurface(surface);
    CreateSwapchain(swapchain);
}

///////////////////////////////////////////////////////////

~Context()
{
    DestroySwapchain(swapchain);
    DestroySurface(surface);
    DestroyDevice(device);
    DestroyPhysical(physical);
    DestroyInstance(instance);
}

///////////////////////////////////////////////////////////

};
}//ns