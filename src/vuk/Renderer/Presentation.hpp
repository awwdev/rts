#pragma once

#include "vuk/Renderer/Context.hpp"
#include "vuk/Renderer/States.hpp"
#include "vuk/Renderer/Commands.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Presentation
{
    VkSemaphore semaphore;

    void Create(Context&);
    void Destroy();
    void Present(Context&, Commands&, States&);
};

///////////////////////////////////////////////////////////

void Presentation::Create(Context&)
{
    VkSemaphoreCreateInfo const semaphoreInfo {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };
    VkCheck(vkCreateSemaphore(g_devicePtr, &semaphoreInfo, nullptr, &semaphore));
}

///////////////////////////////////////////////////////////

void Presentation::Destroy()
{
    vkDestroySemaphore(g_devicePtr, semaphore, nullptr);
}

///////////////////////////////////////////////////////////

void Presentation::Present(Context& context, Commands& commands, States& states)
{
    uint32_t imageIndex = 0;
    VkCheck(vkAcquireNextImageKHR(
        context.device.device, 
        context.swapchain.swapchain, 
        0, 
        semaphore, 
        VK_NULL_HANDLE, 
        &imageIndex
    ));

    VkCheck(vkBeginCommandBuffer(commands.buffer, &commands.beginInfo));
    vkCmdBeginRenderPass(commands.buffer, &states.defaultState.renderPass.beginInfos[imageIndex], VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(commands.buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, states.defaultState.pipeline.pipeline);
    vkCmdDraw(commands.buffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(commands.buffer);
    VkCheck(vkEndCommandBuffer(commands.buffer));

    const VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo const submitInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext                  = nullptr,
        .waitSemaphoreCount     = 1,
        .pWaitSemaphores        = &semaphore,
        .pWaitDstStageMask      = &waitStages,
        .commandBufferCount     = 1,
        .pCommandBuffers        = &commands.buffer,
        .signalSemaphoreCount   = 0,
        .pSignalSemaphores      = nullptr,
    };
    VkCheck(vkQueueSubmit(context.device.queue, 1, &submitInfo, VK_NULL_HANDLE));

    VkPresentInfoKHR const presentInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext                  = nullptr,
        .waitSemaphoreCount     = 0,
        .pWaitSemaphores        = nullptr,
        .swapchainCount         = 1,
        .pSwapchains            = &context.swapchain.swapchain,
        .pImageIndices          = &imageIndex,
        .pResults               = nullptr
    };
    VkCheck(vkQueuePresentKHR(context.device.queue, &presentInfo));

    VkCheck(vkDeviceWaitIdle(g_devicePtr));
}

///////////////////////////////////////////////////////////

}//ns