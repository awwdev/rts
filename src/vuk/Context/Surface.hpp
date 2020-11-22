#pragma once

#include "vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

#ifdef _WIN32 
struct WindowHandle
{
    HINSTANCE hInstance;
    HWND hWnd;
};
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
struct WindowHandle
{
    ::Display* display;
    ::Window window;
};
#endif

///////////////////////////////////////////////////////////

inline void Print_SurfaceCapabilities(VkSurfaceCapabilitiesKHR& surfaceCapabilities)
{
    com::Print(com::ConsoleColor::Yellow, "surfaceCapabilities");
    com::Print("minImageExtent", surfaceCapabilities.minImageExtent.width, surfaceCapabilities.minImageExtent.height);
    com::Print("maxImageExtent", surfaceCapabilities.maxImageExtent.width, surfaceCapabilities.maxImageExtent.height);
}

///////////////////////////////////////////////////////////

static void CreateSurface(
VkSurfaceKHR& surface, 
VkInstance instance, 
VkPhysicalDevice& physical, 
uint32_t queueIndex, 
VkSurfaceCapabilitiesKHR& surfaceCapabilities, 
WindowHandle const& wndHandle)
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
    VkCheck(vkCreateWin32SurfaceKHR(instance, &surfInfo, nullptr, &surface));
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
    VkCheck(vkCreateXlibSurfaceKHR(instance, &surfInfo, nullptr, &surface));
    #endif

    VkBool32 supported;
    VkCheck(vkGetPhysicalDeviceSurfaceSupportKHR(physical, queueIndex, surface, &supported));
    com::PrintBool(supported, "vkGetPhysicalDeviceSurfaceSupportKHR");

    VkCheck(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical, surface, &surfaceCapabilities)); 
    Print_SurfaceCapabilities(surfaceCapabilities);
}

///////////////////////////////////////////////////////////

static void DestroySurface(VkInstance instance, VkSurfaceKHR surface)
{
    vkDestroySurfaceKHR(instance, surface, nullptr);
}

///////////////////////////////////////////////////////////

}//ns