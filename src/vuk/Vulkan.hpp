#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifdef __linux__
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#include "vulkan.h"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

//static VkDevice devicePtr;

///////////////////////////////////////////////////////////

inline void VkCheck(VkResult result)
{
    if (result != VK_SUCCESS)
    {
        com::PrintError("VkResult", result);
    }   
}

///////////////////////////////////////////////////////////

}//ns