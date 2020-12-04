#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"
#include "com/Array.hpp"
#include "com/Optional.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct RenderPass
{
    VkRenderPass renderPass;
    uint32_t width;
    uint32_t height;
    VkFormat format;
    com::Optional<VkClearValue> clear {};

    com::Array<VkFramebuffer, 4> framebuffers;
    com::Array<VkRenderPassBeginInfo, 4> beginInfos;

    void Create(Swapchain&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void RenderPass::Create(Swapchain& swapchain)
{
    width  = swapchain.width;
    height = swapchain.height;
    format = swapchain.format;

    VkAttachmentDescription colorDesc
    {
        .flags          = 0,
        .format         = format, 
        .samples        = VK_SAMPLE_COUNT_1_BIT,
        .loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR,
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
    VkCheck(vkCreateRenderPass(g_devicePtr, &renderPassInfo, GetVkAlloc(), &renderPass));

    auto count = swapchain.images.count;
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
            .clearValueCount= (clear.hasValue ? 1u : 0u),
            .pClearValues   = (clear.hasValue ? &clear.Value() : nullptr),
        };
    }
}

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