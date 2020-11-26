#pragma once

#include "vuk/Renderer/Context.hpp"
#include "vuk/Renderer/States.hpp"
#include "vuk/Renderer/Commands.hpp"
#include "vuk/Renderer/Sync.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Renderer 
{
    Context context;
    States states;
    Commands commands;
    Sync sync;

    uint32_t currentFrame = 0;

    Renderer(WindowHandle const&);
    ~Renderer(); 
    void Update();
    bool CheckSwapchain();
};

///////////////////////////////////////////////////////////

bool Renderer::CheckSwapchain()
{
    if (app::glo::windowHeight <= 0 || app::glo::windowWidth <= 0)
        return false;

    if (app::glo::HasEvent(app::EventEnum::WND_MOVE_SIZE))
    {
        vkDeviceWaitIdle(g_devicePtr);

        commands.Destroy();
        states.Destroy();
        context.swapchain.Destroy();

        context.surface.UpdateSurfaceCapabilities(context.physical);
        context.swapchain.Create(context.device, context.surface);
        states.Create(context); 
        commands.Create(context.physical.queueIndex, context.swapchain);
    }

    return true;
}

///////////////////////////////////////////////////////////

Renderer::Renderer(WindowHandle const& wndHandle)
{
    context.Create(wndHandle);
    states.Create(context); 
    commands.Create(context.physical.queueIndex, context.swapchain);
    sync.Create(context.swapchain);
}

///////////////////////////////////////////////////////////

Renderer::~Renderer()
{
    vkDeviceWaitIdle(g_devicePtr);
    sync.Destroy();
    commands.Destroy();
    states.Destroy();
    context.Destroy();
}

///////////////////////////////////////////////////////////

void Renderer::Update()
{
    if (CheckSwapchain() == false)
        return;

    if (vkWaitForFences(g_devicePtr, 1, &sync.fences[currentFrame], VK_FALSE, 0) != VK_SUCCESS)
        return;

    uint32_t imageIndex = 0;
    auto res = vkAcquireNextImageKHR(
        context.device.device, 
        context.swapchain.swapchain, 
        0, 
        sync.imageAcquired[currentFrame], 
        VK_NULL_HANDLE, 
        &imageIndex
    );
    if (res != VK_SUCCESS)
        return;

    if (sync.inFlight[imageIndex] != VK_NULL_HANDLE) 
        vkWaitForFences(g_devicePtr, 1, &sync.inFlight[imageIndex], VK_FALSE, UINT64_MAX);
    sync.inFlight[imageIndex] = sync.fences[currentFrame];
    VkCheck(vkResetFences(g_devicePtr, 1, &sync.fences[currentFrame]));

    ///////////////////////////////////////////////////////////
    states.Record(commands, imageIndex);
    ///////////////////////////////////////////////////////////

    const VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo const submitInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext                  = nullptr,
        .waitSemaphoreCount     = 1,
        .pWaitSemaphores        = &sync.imageAcquired[currentFrame],
        .pWaitDstStageMask      = &waitStages,
        .commandBufferCount     = 1,
        .pCommandBuffers        = &commands.buffers[imageIndex],
        .signalSemaphoreCount   = 1,
        .pSignalSemaphores      = &sync.imageFinished[currentFrame],
    };
    VkCheck(vkQueueSubmit(context.device.queue, 1, &submitInfo, sync.fences[currentFrame]));

    VkPresentInfoKHR const presentInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext                  = nullptr,
        .waitSemaphoreCount     = 1,
        .pWaitSemaphores        = &sync.imageFinished[currentFrame],
        .swapchainCount         = 1,
        .pSwapchains            = &context.swapchain.swapchain,
        .pImageIndices          = &imageIndex,
        .pResults               = nullptr
    };
    auto res2 = vkQueuePresentKHR(context.device.queue, &presentInfo);
    if (res2 != VK_SUCCESS)
        com::PrintWarning("vkQueuePresentKHR not success", res2);

    currentFrame = (currentFrame + 1) % (context.swapchain.images.count - 1);
}

///////////////////////////////////////////////////////////

}//ns