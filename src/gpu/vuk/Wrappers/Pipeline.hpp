#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PipelineExt.hpp"
#include "gpu/vuk/Wrappers/Shader.hpp"
#include "gpu/vuk/Wrappers/RenderPass.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct Pipeline
{
    VkPipeline pipeline;
    VkPipelineLayout layout;
    void Create(FragVertShader&, RenderPass&, PipelineInfo&);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Pipeline::Create(FragVertShader& shader, RenderPass& renderPass, PipelineInfo& pipelineInfo)
{
    VkCheck(vkCreatePipelineLayout(g_devicePtr, &pipelineInfo.layoutInfo, GetVkAlloc(), &layout));

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
    
    VkCheck(vkCreateGraphicsPipelines(g_devicePtr, VK_NULL_HANDLE, 1, &createInfo, GetVkAlloc(), &pipeline));
}

///////////////////////////////////////////////////////////

void Pipeline::Destroy()
{
    vkDestroyPipeline(g_devicePtr, pipeline, GetVkAlloc());
    vkDestroyPipelineLayout(g_devicePtr, layout, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns