#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifdef __linux__
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#include "vulkan.h"
#include "com/Print.hpp"
#include "com/Assert.hpp"
#include "com/Array.hpp"
#include <cstring>

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

constexpr bool ENABLE_VK_CHECK = true;
inline VkDevice g_devicePtr;

///////////////////////////////////////////////////////////

inline void VkCheck(VkResult result)
{
    if constexpr(ENABLE_VK_CHECK == false)
        return;

    if (result != VK_SUCCESS)
        com::Assert(false, "VkResult", result);
}

///////////////////////////////////////////////////////////

void* AllocationFunction(
    void*                                       pUserData,
    size_t                                      size,
    size_t                                      alignment,
    VkSystemAllocationScope                     allocationScope)
{
    //com::Print("alloc", size);
    //auto addr = bufferPtr;
    //bufferPtr += size;
    //return addr;
    return nullptr;
}

///////////////////////////////////////////////////////////

void FreeFunction(
    void*                                       pUserData,
    void*                                       pMemory)
{
}

///////////////////////////////////////////////////////////

void* ReallocationFunction(
    void*                                       pUserData,
    void*                                       pOriginal,
    size_t                                      size,
    size_t                                      alignment,
    VkSystemAllocationScope                     allocationScope)
{
    //auto addr = bufferPtr;
    //std::memcpy(addr, pOriginal, size);
    //bufferPtr += size;
    //return addr;
    return nullptr;
}

///////////////////////////////////////////////////////////

const VkAllocationCallbacks alloc
{
    .pUserData = nullptr,
    .pfnAllocation = AllocationFunction,
    .pfnReallocation = ReallocationFunction,
    .pfnFree = FreeFunction,
    .pfnInternalAllocation = nullptr,
    .pfnInternalFree = nullptr,
};

///////////////////////////////////////////////////////////

inline const VkAllocationCallbacks* GetVkAlloc()
{
    return nullptr;
    //return &alloc;
}

///////////////////////////////////////////////////////////

}//ns