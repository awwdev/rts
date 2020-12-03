#pragma once

#include "gpu/vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

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

inline void PrintSurfaceCapabilities(VkSurfaceCapabilitiesKHR& surfaceCapabilities)
{
    com::Print(com::ConsoleColor::Yellow, "surfaceCapabilities");
    com::Print("minImageExtent", surfaceCapabilities.minImageExtent.width, surfaceCapabilities.minImageExtent.height);
    com::Print("maxImageExtent", surfaceCapabilities.maxImageExtent.width, surfaceCapabilities.maxImageExtent.height);
}

///////////////////////////////////////////////////////////

}//ns