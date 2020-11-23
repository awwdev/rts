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

Instance  instance;
Physical  physical;
Device    device;
Surface   surface;
Swapchain swapchain;

///////////////////////////////////////////////////////////

Context(WindowHandle const& wndHandle)
{
    CreateInstance  (instance, VK_API_VERSION_1_0);
    CreatePhysical  (instance.instance, physical);
    CreateDevice    (device, physical);
    CreateSurface   (surface, instance.instance, physical, wndHandle);
    CreateSwapchain (device.device, swapchain, surface, 
    VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR, VK_PRESENT_MODE_FIFO_KHR);
    //VK_PRESENT_MODE_IMMEDIATE_KHR
}

///////////////////////////////////////////////////////////

~Context()
{
    DestroySwapchain(device.device, swapchain);
    DestroySurface  (instance.instance, surface);
    DestroyDevice   (device);
    DestroyInstance (instance);
    g_devicePtr = nullptr;
}

///////////////////////////////////////////////////////////

};
}//ns