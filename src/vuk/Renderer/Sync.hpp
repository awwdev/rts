#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Swapchain.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Sync
{
    com::SimpleArray<VkSemaphore, 4> imageAcquired;
    com::SimpleArray<VkSemaphore, 4> imageFinished;
    com::SimpleArray<VkFence, 4> fences;
    com::SimpleArray<VkFence, 4> inFlight {};

    void Create(Swapchain&);
    void Destroy();
};

////////////////////////////////////////////////////////////

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

    FOR_SIMPLE_ARRAY(imageAcquired, i) 
        vkCreateSemaphore(g_devicePtr, &semaphoreInfo, GetAlloc(), &imageAcquired[i]);    
    FOR_SIMPLE_ARRAY(imageFinished, i) 
        vkCreateSemaphore(g_devicePtr, &semaphoreInfo, GetAlloc(), &imageFinished[i]);  
    FOR_SIMPLE_ARRAY(fences, i) 
        vkCreateFence(g_devicePtr, &fenceInfo, GetAlloc(), &fences[i]);
    
}

////////////////////////////////////////////////////////////

void Sync::Destroy()
{
    FOR_SIMPLE_ARRAY(imageAcquired, i) 
        vkDestroySemaphore(g_devicePtr, imageAcquired[i], GetAlloc());
    FOR_SIMPLE_ARRAY(imageFinished, i) 
        vkDestroySemaphore(g_devicePtr, imageFinished[i], GetAlloc());
    FOR_SIMPLE_ARRAY(fences, i)        
        vkDestroyFence(g_devicePtr, fences[i], GetAlloc());

    imageAcquired.count = 0;
    imageFinished.count = 0;
    fences.count = 0;
    inFlight.count = 0;
}

////////////////////////////////////////////////////////////

}//ns