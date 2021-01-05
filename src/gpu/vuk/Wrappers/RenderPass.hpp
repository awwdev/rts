#pragma once

#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/vuk/Context/Context.hpp"
#include "gpu/vuk/Wrappers/RenderPassExt.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct RenderPass
{
    VkRenderPass renderPass;
    uint32_t width;
    uint32_t height;
    VkFormat format;
    SwapResource<VkFramebuffer> framebuffers;
    SwapResource<VkRenderPassBeginInfo> beginInfos;
    void Destroy();
};

///////////////////////////////////////////////////////////

void RenderPass::Destroy()
{
    vkDestroyRenderPass(g_devicePtr, renderPass, GetVkAlloc());  
    DestroySwapResource(framebuffers);
    DestroySwapResource(beginInfos);
}

///////////////////////////////////////////////////////////

}//ns