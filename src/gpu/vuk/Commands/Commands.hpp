#pragma once

#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/vuk/Commands/CommandsExt.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"
#include "com/Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct Commands 
{
    VkCommandPool pool;
    SwapResource<VkCommandBuffer> buffers;
    void Create(uint32_t, Swapchain&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Commands::Create(uint32_t queueIdx, Swapchain& swapchain)
{
    VkCommandPoolCreateInfo poolInfo
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,//!VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = queueIdx
    };
    VkCheck(vkCreateCommandPool(g_devicePtr, &poolInfo, GetVkAlloc(), &pool));

    VkCommandBufferAllocateInfo allocInfo
    {
        .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext              = nullptr,
        .commandPool        = pool,
        .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = swapchain.Count()
    };
    buffers.count = swapchain.Count();
    VkCheck(vkAllocateCommandBuffers(g_devicePtr, &allocInfo, buffers.data));
}

///////////////////////////////////////////////////////////

void Commands::Destroy()
{
    vkFreeCommandBuffers(g_devicePtr, pool, buffers.count, buffers.data);
    vkDestroyCommandPool(g_devicePtr, pool,  GetVkAlloc());
    buffers.count = 0;
}

///////////////////////////////////////////////////////////

}//ns