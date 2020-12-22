#pragma once

#include "gpu/vuk/Wrappers/RenderPass.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"
#include "gpu/vuk/Renderer/Commands.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct SpritesRenderPass : RenderPass
{
    Image shadows;
    com::POD_Array<VkFramebuffer, 4> shadowFrameBuffers;
    com::POD_Array<VkRenderPassBeginInfo, 4> shadowBeginInfos;

    Image offscreen;
    VkClearValue clear;
    VkClearValue shadowClears;
    void Create(VkCommandPool, Swapchain&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void SpritesRenderPass::Create(VkCommandPool cmdPool, Swapchain& swapchain)
{
    clear = { VkClearValue { .color { 155/255.f, 186/255.f, 94/255.f, 1.f } } };
    shadowClears = { VkClearValue { .color { } } };

    width  = swapchain.width;
    height = swapchain.height;
    format = swapchain.format;

    shadows.Create(cmdPool, format, 
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D,
        width, height, 1
    );

    offscreen.Create(cmdPool, format, 
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D,
        width, height, 1
    );

    VkAttachmentDescription colorDesc
    {
        .flags          = 0,
        .format         = format, 
        .samples        = VK_SAMPLE_COUNT_1_BIT,
        .loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR, //!
        .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout    = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL //!
    };
    offscreen.layout = colorDesc.finalLayout;
    shadows.layout = colorDesc.finalLayout;

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
        .pDependencies   = &dependency,
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
            .pAttachments    = &offscreen.view,
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
            .clearValueCount= 1,
            .pClearValues   = &clear,
        };
    }

    //shadow
    count = swapchain.images.count;
    shadowFrameBuffers.count = count;
    shadowBeginInfos.count = count;

    for(uint32_t i = 0; i < count; ++i)
    {
        VkFramebufferCreateInfo framebufferInfo 
        {
            .sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .pNext           = nullptr,
            .flags           = 0,
            .renderPass      = renderPass,
            .attachmentCount = 1,
            .pAttachments    = &shadows.view,
            .width           = width,
            .height          = height,
            .layers          = 1
        };
        VkCheck(vkCreateFramebuffer(g_devicePtr, &framebufferInfo, GetVkAlloc(), &shadowFrameBuffers[i]));

        shadowBeginInfos[i] = 
        {
            .sType          = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext          = nullptr, 
            .renderPass     = renderPass,
            .framebuffer    = shadowFrameBuffers[i],
            .renderArea     = {
                .offset     = VkOffset2D {0, 0},
                .extent     = { width, height }
            },
            .clearValueCount= 1,
            .pClearValues   = &shadowClears,
        };
    }
}

///////////////////////////////////////////////////////////

void SpritesRenderPass::Destroy()
{
    RenderPass::Destroy();
    shadows.Destroy();
    offscreen.Destroy();

    FOR_ARRAY(shadowFrameBuffers, i)
    {
        vkDestroyFramebuffer(g_devicePtr, shadowFrameBuffers[i], GetVkAlloc());
        shadowFrameBuffers[i] = nullptr;
    }
    shadowFrameBuffers.count = 0;
    FOR_ARRAY(shadowBeginInfos, i)
    {
        shadowBeginInfos[i] = {};
    }
    shadowBeginInfos.count = 0;
}

///////////////////////////////////////////////////////////

}//ns