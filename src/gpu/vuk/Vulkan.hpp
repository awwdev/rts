#pragma once

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifdef __linux__
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#include "vulkan.h"
#include "com/Print.hpp"
#include <cstring>

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

    static VkDevice g_devicePtr;
    constexpr bool ENABLE_VK_CHECK = true;

    alignas(8) inline char buffer [10'000'000]; 
    alignas(8) inline char* bufferPtr = buffer;

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

void* AllocationFunction(
    void*                                       pUserData,
    size_t                                      size,
    size_t                                      alignment,
    VkSystemAllocationScope                     allocationScope)
{
    //com::Print("alloc", size);
    auto addr = bufferPtr;
    bufferPtr += size;
    return addr;
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
    auto addr = bufferPtr;
    std::memcpy(addr, pOriginal, size);
    bufferPtr += size;
    return addr;
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

inline const VkAllocationCallbacks* GetAlloc()
{
    return nullptr;
    //return &alloc;
}

///////////////////////////////////////////////////////////

}//ns