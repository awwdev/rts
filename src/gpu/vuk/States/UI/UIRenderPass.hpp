#pragma once

#include "gpu/vuk/Wrappers/RenderPass.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct RenderPassUI : RenderPass
{
    void Create(Swapchain& swapchain);
    void Destroy();
};

///////////////////////////////////////////////////////////

inline void RenderPassUI::Create(Swapchain& swapchain)
{
    width  = swapchain.width;
    height = swapchain.height;

    auto colorDesc = AttachmentDescription(
        swapchain.format, 
        VK_ATTACHMENT_LOAD_OP_LOAD, 
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    );

    auto colorRef = ColorAttachmentReference();
    auto subpass  = SubpassDescription(colorRef);

    VkRenderPassCreateInfo renderPassInfo 
    {
        .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext           = nullptr,
        .flags           = 0,
        .attachmentCount = 1,
        .pAttachments    = &colorDesc,
        .subpassCount    = 1,
        .pSubpasses      = &subpass,
        .dependencyCount = 0, //! maybe wrong
        .pDependencies   = nullptr
    };
    VkCheck(vkCreateRenderPass(g_devicePtr, &renderPassInfo, GetVkAlloc(), &renderPass));

    auto count = swapchain.Count();
    framebuffers.count = count;
    beginInfos.count = count;

    for(uint32_t i = 0; i < count; ++i)
    {
        VkFramebufferCreateInfo framebufferInfo 
        {
            .sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .pNext           = nullptr,
            .flags           = 0,
            .renderPass      = renderPass,
            .attachmentCount = 1,
            .pAttachments    = &swapchain.views[i],
            .width           = width,
            .height          = height,
            .layers          = 1
        };
        VkCheck(vkCreateFramebuffer(g_devicePtr, &framebufferInfo, GetVkAlloc(), &framebuffers[i]));

        beginInfos[i] = 
        {
            .sType          = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext          = nullptr, 
            .renderPass     = renderPass,
            .framebuffer    = framebuffers[i],
            .renderArea     = {
                .offset     = VkOffset2D {0, 0},
                .extent     = { width, height }
            },
            .clearValueCount= 0,
            .pClearValues   = nullptr,
        };
    }
}

///////////////////////////////////////////////////////////

void RenderPassUI::Destroy()
{
    RenderPass::Destroy();
}

///////////////////////////////////////////////////////////

}//ns