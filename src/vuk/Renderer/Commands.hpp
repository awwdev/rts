#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Renderer/CommandsExt.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

////////////////////////////////////////////////////////////

struct Commands 
{
    VkCommandPool pool;
    VkCommandBuffer buffer;
    VkCommandBufferBeginInfo beginInfo = CreateCmdBeginInfo();

    void Create(uint32_t);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Commands::Create(uint32_t queueIdx)
{
    VkCommandPoolCreateInfo poolInfo
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = nullptr,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = queueIdx
    };
    VkCheck(vkCreateCommandPool(g_devicePtr, &poolInfo, GetAlloc(), &pool));

    VkCommandBufferAllocateInfo allocInfo
    {
        .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext              = nullptr,
        .commandPool        = pool,
        .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };
    VkCheck(vkAllocateCommandBuffers(g_devicePtr, &allocInfo, &buffer));
}

///////////////////////////////////////////////////////////

void Commands::Destroy()
{
    vkFreeCommandBuffers(g_devicePtr, pool, 1, &buffer);
    vkDestroyCommandPool(g_devicePtr, pool,  GetAlloc());
}

///////////////////////////////////////////////////////////

}//ns