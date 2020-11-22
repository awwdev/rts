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

static VkDevice g_devicePtr;
constexpr bool ENABLE_VK_CHECK = true;

///////////////////////////////////////////////////////////

inline void VkCheck(VkResult result)
{
    if constexpr(ENABLE_VK_CHECK == false)
        return;

    if (result != VK_SUCCESS)
    {
        com::PrintError("VkResult", result);
        __builtin_trap();
    }   
}

///////////////////////////////////////////////////////////

}//ns