#pragma once

#include "gpu/vuk/Wrappers/RenderPass.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreatePostRenderPass(RenderPass& rp, Swapchain& swapchain)
{
    rp.width  = swapchain.width;
    rp.height = swapchain.height;
    rp.format = swapchain.format;

    VkAttachmentDescription colorDesc
    {
        .flags          = 0,
        .format         = rp.format, 
        .samples        = VK_SAMPLE_COUNT_1_BIT,
        .loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE, //!
        .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };

    VkAttachmentReference colorRef
    {
        .attachment = 0,
        .layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkSubpassDescription subpass 
    {
        .flags                   = 0,
        .pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount    = 0,
        .pInputAttachments       = nullptr,
        .colorAttachmentCount    = 1,
        .pColorAttachments       = &colorRef,
        .pResolveAttachments     = nullptr,
        .pDepthStencilAttachment = nullptr,
        .preserveAttachmentCount = 0,
        .pPreserveAttachments    = nullptr
    };

    VkSubpassDependency dependency 
    {
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
        .dependencyFlags = 0
    };

    VkRenderPassCreateInfo renderPassInfo 
    {
        .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext           = nullptr,
        .flags           = 0,
        .attachmentCount = 1,
        .pAttachments    = &colorDesc,
        .subpassCount    = 1,
        .pSubpasses      = &subpass,
        .dependencyCount = 1,
        .pDependencies   = &dependency
    };
    VkCheck(vkCreateRenderPass(g_devicePtr, &renderPassInfo, GetVkAlloc(), &rp.renderPass));

    auto count = swapchain.images.count;
    rp.framebuffers.count = count;
    rp.beginInfos.count = count;

    for(uint32_t i = 0; i < count; ++i)
    {
        VkFramebufferCreateInfo framebufferInfo 
        {
            .sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .pNext           = nullptr,
            .flags           = 0,
            .renderPass      = rp.renderPass,
            .attachmentCount = 1,
            .pAttachments    = &swapchain.views[i],
            .width           = rp.width,
            .height          = rp.height,
            .layers          = 1
        };
        VkCheck(vkCreateFramebuffer(g_devicePtr, &framebufferInfo, GetVkAlloc(), &rp.framebuffers[i]));

        rp.beginInfos[i] = 
        {
            .sType          = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext          = nullptr, 
            .renderPass     = rp.renderPass,
            .framebuffer    = rp.framebuffers[i],
            .renderArea     = {
                .offset     = VkOffset2D {0, 0},
                .extent     = { rp.width, rp.height }
            },
            .clearValueCount= (rp.clear.hasValue ? 1u : 0u),
            .pClearValues   = (rp.clear.hasValue ? &rp.clear.Value() : nullptr),
        };
    }
}

///////////////////////////////////////////////////////////

}//ns