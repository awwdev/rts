#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Renderer/Context.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct RenderPass
{
    VkRenderPass renderPass;
    uint32_t width;
    uint32_t height;
    VkFormat format;
    com::Array<VkFramebuffer, 4> framebuffers;
    com::Array<VkRenderPassBeginInfo, 4> beginInfos;
    void Destroy();
};

///////////////////////////////////////////////////////////

void RenderPass::Destroy()
{
    vkDestroyRenderPass(g_devicePtr, renderPass, GetVkAlloc());
    FOR_ARRAY(framebuffers, i)
    {
        vkDestroyFramebuffer(g_devicePtr, framebuffers[i], GetVkAlloc());
        framebuffers[i] = nullptr;
    }
    framebuffers.count = 0;

    FOR_ARRAY(beginInfos, i)
    {
        beginInfos[i] = {};
    }
    beginInfos.count = 0;
}

///////////////////////////////////////////////////////////

}//ns