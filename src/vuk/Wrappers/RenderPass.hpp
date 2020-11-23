#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Swapchain.hpp"

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct RenderPass
{
    VkRenderPass renderPass;
    uint32_t width;
    uint32_t height;
    VkFormat format;

    uint32_t framebufferCount;
    VkFramebuffer* framebuffers;
    VkRenderPassBeginInfo* beginInfos;
    VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_1_BIT;

    void Create(Swapchain&);
    void Destroy();
};

////////////////////////////////////////////////////////////

void RenderPass::Create(Swapchain& swapchain)
{
    width  = swapchain.width;
    height = swapchain.height;
    format = swapchain.format;

    VkAttachmentDescription colorDesc
    {
        .flags          = 0,
        .format         = format, 
        .samples        = sampleCount,
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

    VkSubpassDescription subpassDesc 
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

    const VkSubpassDependency dependencies []
    {
        {
            .srcSubpass         = VK_SUBPASS_EXTERNAL,
            .dstSubpass         = 0,
            .srcStageMask       = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            .dstStageMask       = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask      = VK_ACCESS_MEMORY_READ_BIT,
            .dstAccessMask      = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dependencyFlags    = VK_DEPENDENCY_BY_REGION_BIT,
        },
        {
            .srcSubpass         = 0,
            .dstSubpass         = VK_SUBPASS_EXTERNAL,
            .srcStageMask       = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask       = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            .srcAccessMask      = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dstAccessMask      = VK_ACCESS_MEMORY_READ_BIT,
            .dependencyFlags    = VK_DEPENDENCY_BY_REGION_BIT,
        }
    };

    VkRenderPassCreateInfo renderPassInfo 
    {
        .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext           = nullptr,
        .flags           = 0,
        .attachmentCount = 1,
        .pAttachments    = &colorDesc,
        .subpassCount    = 1,
        .pSubpasses      = &subpassDesc,
        .dependencyCount = array_extent(dependencies),
        .pDependencies   = dependencies
    };
    VkCheck(vkCreateRenderPass(g_devicePtr, &renderPassInfo, nullptr, &renderPass));

    framebufferCount = swapchain.swapImagesCount;
    framebuffers = new VkFramebuffer[framebufferCount];
    beginInfos = new VkRenderPassBeginInfo[framebufferCount];

    for(uint32_t i = 0; i < framebufferCount; ++i)
    {
        VkFramebufferCreateInfo framebufferInfo 
        {
            .sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .pNext           = nullptr,
            .flags           = 0,
            .renderPass      = renderPass,
            .attachmentCount = 1,
            .pAttachments    = &swapchain.swapImageViews[i],
            .width           = width,
            .height          = height,
            .layers          = 1
        };
        VkCheck(vkCreateFramebuffer(g_devicePtr, &framebufferInfo, nullptr, &framebuffers[i]));

        VkClearValue clear = { .color { 0.1, 0.1, 0.1, 1 } };
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
            .pClearValues   = &clear
        };
    }
}

////////////////////////////////////////////////////////////

void RenderPass::Destroy()
{
    vkDestroyRenderPass(g_devicePtr, renderPass, nullptr);
    for(uint32_t i = 0; i < framebufferCount; ++i)
    {
        vkDestroyFramebuffer(g_devicePtr, framebuffers[i], nullptr);
    }
    delete[] framebuffers;
}

////////////////////////////////////////////////////////////

}//ns