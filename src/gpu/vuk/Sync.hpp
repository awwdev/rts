#pragma once

#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct Sync
{
    SwapResource<VkSemaphore> imageAcquired;
    SwapResource<VkSemaphore> imageFinished;
    SwapResource<VkFence> fences;
    SwapResource<VkFence> inFlight;

    void Create(Swapchain&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Sync::Create(Swapchain& swapchain)
{
    imageAcquired.count = swapchain.Count();
    imageFinished.count = swapchain.Count();
    fences.count = swapchain.Count();
    inFlight.count = swapchain.Count();

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
    DestroySwapResource(imageAcquired);
    DestroySwapResource(imageFinished);
    DestroySwapResource(fences);
}

///////////////////////////////////////////////////////////

}//ns