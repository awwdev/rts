#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Context/SurfaceExt.hpp"
#include "gpu/vuk/Context/Instance.hpp"
#include "gpu/vuk/Context/Physical.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct Surface 
{
    VkSurfaceKHR surface;
    VkSurfaceCapabilitiesKHR capabilities;

    void Create(Instance&, Physical&, WindowHandle const&);
    void Destroy(Instance&);
    void UpdateSurfaceCapabilities(Physical&);
};

///////////////////////////////////////////////////////////

void Surface::Create(Instance& instance, Physical& physical, WindowHandle const& wndHandle)
{
#ifdef _WIN32
    VkWin32SurfaceCreateInfoKHR const surfInfo 
    {
        .sType      = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .pNext      = nullptr,
        .flags      = 0,
        .hinstance  = wndHandle.hInstance,
        .hwnd       = wndHandle.hWnd,
    };
    VkCheck(vkCreateWin32SurfaceKHR(instance.instance, &surfInfo, GetAlloc(), &surface));
#endif

#ifdef __linux__
    VkXlibSurfaceCreateInfoKHR const surfInfo 
    {
        .sType  = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
        .pNext  = nullptr, 
        .flags  = 0,
        .dpy    = wndHandle.display,
        .window = wndHandle.window
    };
    VkCheck(vkCreateXlibSurfaceKHR(instance.instance, &surfInfo, nullptr, &surface));
#endif

    UpdateSurfaceCapabilities(physical);
}

///////////////////////////////////////////////////////////

void Surface::Destroy(Instance& instance)
{
    vkDestroySurfaceKHR(instance.instance, surface, GetAlloc());
}

///////////////////////////////////////////////////////////

void Surface::UpdateSurfaceCapabilities(Physical& physical)
{
    VkBool32 supported;
    VkCheck(vkGetPhysicalDeviceSurfaceSupportKHR(physical.physical, physical.queueIndex, surface, &supported));
    //com::PrintBool(supported, "vkGetPhysicalDeviceSurfaceSupportKHR");
    VkCheck(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical.physical, surface, &capabilities)); 
    //Print_SurfaceCapabilities(surfaceCapabilities);
}

///////////////////////////////////////////////////////////

}//ns