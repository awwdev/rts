#pragma once

#include "gpu/vuk/Wrappers/RenderPass.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"
#include "gpu/vuk/Commands/Commands.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct RenderPassGeneral : RenderPass
{
    SwapResource<Image> offscreen;
    VkClearValue clear;
    void Create(VkCommandPool, Swapchain&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void RenderPassGeneral::Create(VkCommandPool cmdPool, Swapchain& swapchain)
{
    clear = { VkClearValue { .color { 155/255.f, 186/255.f, 94/255.f, 1.f } } };
    width  = swapchain.width;
    height = swapchain.height;

    auto colorDesc = AttachmentDescription(
        swapchain.format, 
        VK_ATTACHMENT_LOAD_OP_CLEAR, 
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    );

    offscreen.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(offscreen, i)
    {
        offscreen[i].Create(cmdPool, swapchain.format, 
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
            VK_IMAGE_VIEW_TYPE_2D,
            width, height, 1
        );
        offscreen[i].layout = colorDesc.finalLayout;
    }

    auto colorRef = ColorAttachmentReference();
    auto subpass  = SubpassDescription(colorRef);

    VkSubpassDependency dependencies [2] {};
    dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[0].dstSubpass = 0;
    dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
    dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    dependencies[1].srcSubpass = 0;
    dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    VkRenderPassCreateInfo renderPassInfo 
    {
        .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext           = nullptr,
        .flags           = 0,
        .attachmentCount = 1,
        .pAttachments    = &colorDesc,
        .subpassCount    = 1,
        .pSubpasses      = &subpass,
        .dependencyCount = 2, //! FIXED FLICKERING
        .pDependencies   = dependencies,
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
            .pAttachments    = &offscreen[i].view,
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
}

///////////////////////////////////////////////////////////

void RenderPassGeneral::Destroy()
{
    RenderPass::Destroy();
    DestroySwapResource(offscreen);
}

///////////////////////////////////////////////////////////

}//ns