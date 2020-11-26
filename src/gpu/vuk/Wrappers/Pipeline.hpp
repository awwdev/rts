#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PipelineExt.hpp"
#include "gpu/vuk/Wrappers/Shader.hpp"
#include "gpu/vuk/Wrappers/RenderPass.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct Pipeline
{
    VkPipeline pipeline;
    VkPipelineLayout layout;
    void Create(Shader&, RenderPass&, PipelineInfo&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Pipeline::Destroy()
{
    vkDestroyPipeline(g_devicePtr, pipeline, GetAlloc());
    vkDestroyPipelineLayout(g_devicePtr, layout, GetAlloc());
}

///////////////////////////////////////////////////////////

void Pipeline::Create(Shader& shader, RenderPass& renderPass, PipelineInfo& pipelineInfo)
{
    VkCheck(vkCreatePipelineLayout(g_devicePtr, &pipelineInfo.layoutInfo, GetAlloc(), &layout));

    VkGraphicsPipelineCreateInfo createInfo
    {
        .sType                      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext                      = nullptr,
        .flags                      = 0,
        .stageCount                 = (uint32_t)array_extent(shader.stageInfos),
        .pStages                    = shader.stageInfos,
        .pVertexInputState          = &pipelineInfo.vertexInput,
        .pInputAssemblyState        = &pipelineInfo.inputAssembly,
        .pTessellationState         = nullptr,
        .pViewportState             = &pipelineInfo.viewportState.stateInfo,
        .pRasterizationState        = &pipelineInfo.rasterization,
        .pMultisampleState          = &pipelineInfo.multisampling,
        .pDepthStencilState         = &pipelineInfo.depthStencil,
        .pColorBlendState           = &pipelineInfo.blendState.stateInfo,
        .pDynamicState              = nullptr,
        .layout                     = layout,
        .renderPass                 = renderPass.renderPass,
        .subpass                    = 0,
        .basePipelineHandle         = VK_NULL_HANDLE,
        .basePipelineIndex          = -1
    };
    
    VkCheck(vkCreateGraphicsPipelines(g_devicePtr, VK_NULL_HANDLE, 1, &createInfo, GetAlloc(), &pipeline));
}

///////////////////////////////////////////////////////////

}//ns