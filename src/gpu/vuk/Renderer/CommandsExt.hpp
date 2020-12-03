#pragma once

#include "gpu/vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline VkCommandBufferBeginInfo CreateCmdBeginInfo(VkCommandBufferUsageFlags flags = 0)
{
    return {
        .sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext            = nullptr,
        .flags            = flags,
        .pInheritanceInfo = nullptr
    };
}

///////////////////////////////////////////////////////////

inline VkCommandBuffer BeginCommands_OneTime(VkCommandPool cmdPool)
{
    VkCommandBuffer commandBuffer;

    VkCommandBufferAllocateInfo allocInfo 
    {
        .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext              = nullptr,
        .commandPool        = cmdPool,
        .level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };
    VkCheck(vkAllocateCommandBuffers(g_devicePtr, &allocInfo, &commandBuffer));

    auto beginInfo = CreateCmdBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    VkCheck(vkBeginCommandBuffer(commandBuffer, &beginInfo));
    
    return commandBuffer;
}

///////////////////////////////////////////////////////////

inline void EndCommands_OneTime(VkCommandBuffer cmdBuffer, VkCommandPool cmdPool)
{
    VkCheck(vkEndCommandBuffer(cmdBuffer));

    VkSubmitInfo submitInfo 
    {
        .sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext                = nullptr,
        .waitSemaphoreCount   = 0,
        .pWaitSemaphores      = nullptr,
        .pWaitDstStageMask    = nullptr,
        .commandBufferCount   = 1,
        .pCommandBuffers      = &cmdBuffer,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores    = nullptr
    };

    VkCheck(vkQueueSubmit(g_contextPtr->device.queue, 1, &submitInfo, VK_NULL_HANDLE));
    VkCheck(vkQueueWaitIdle(g_contextPtr->device.queue));
    vkFreeCommandBuffers(g_devicePtr, cmdPool, 1, &cmdBuffer);
}

///////////////////////////////////////////////////////////

}//ns