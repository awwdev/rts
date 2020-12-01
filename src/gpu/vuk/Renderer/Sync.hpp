#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct Sync
{
    com::Array<VkSemaphore, 4> imageAcquired;
    com::Array<VkSemaphore, 4> imageFinished;
    com::Array<VkFence, 4> fences;
    com::Array<VkFence, 4> inFlight {};

    void Create(Swapchain&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Sync::Create(Swapchain& swapchain)
{
    imageAcquired.count = swapchain.images.count;
    imageFinished.count = swapchain.images.count;
    fences.count = swapchain.images.count;
    inFlight.count = swapchain.images.count;

    VkSemaphoreCreateInfo semaphoreInfo 
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };

    VkFenceCreateInfo fenceInfo 
    { 
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, 
        .pNext = nullptr, 
        .flags = VK_FENCE_CREATE_SIGNALED_BIT 
    };

    FOR_ARRAY(imageAcquired, i) 
        vkCreateSemaphore(g_devicePtr, &semaphoreInfo, GetVkAlloc(), &imageAcquired[i]);    
    FOR_ARRAY(imageFinished, i) 
        vkCreateSemaphore(g_devicePtr, &semaphoreInfo, GetVkAlloc(), &imageFinished[i]);  
    FOR_ARRAY(fences, i) 
        vkCreateFence(g_devicePtr, &fenceInfo, GetVkAlloc(), &fences[i]);
    
}

///////////////////////////////////////////////////////////

void Sync::Destroy()
{
    FOR_ARRAY(imageAcquired, i) 
        vkDestroySemaphore(g_devicePtr, imageAcquired[i], GetVkAlloc());
    FOR_ARRAY(imageFinished, i) 
        vkDestroySemaphore(g_devicePtr, imageFinished[i], GetVkAlloc());
    FOR_ARRAY(fences, i)        
        vkDestroyFence(g_devicePtr, fences[i], GetVkAlloc());

    imageAcquired.count = 0;
    imageFinished.count = 0;
    fences.count = 0;
    inFlight.count = 0;
}

///////////////////////////////////////////////////////////

}//ns