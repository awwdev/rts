#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Wrappers/PipelineExt.hpp"
#include "vuk/Wrappers/Shader.hpp"
#include "vuk/Wrappers/RenderPass.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Pipeline
{
    VkPipeline pipeline;
    VkPipelineLayout layout;

    void Create(Shader&, RenderPass&);
    void Destroy();
};

////////////////////////////////////////////////////////////

void Pipeline::Create(Shader& shader, RenderPass& renderPass)
{
    auto layoutInfo = PipelineLayout();
    VkCheck(vkCreatePipelineLayout(g_devicePtr, &layoutInfo, nullptr, &layout));

    auto vertexInput = VertexInput();
    auto inputAssembly = InputAssembly();
    auto viewportState = ViewportState(renderPass.width, renderPass.height);
    auto multisampling = Multisampling();
    auto rasterization = Rasterization();
    auto depthStencil = DepthStencil();
    auto blendState = BlendStateInfo();

    VkGraphicsPipelineCreateInfo pipelineInfo
    {
        .sType                      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext                      = nullptr,
        .flags                      = 0,
        .stageCount                 = (uint32_t)array_extent(shader.stageInfos),
        .pStages                    = shader.stageInfos,
        .pVertexInputState          = &vertexInput,
        .pInputAssemblyState        = &inputAssembly,
        .pTessellationState         = nullptr,
        .pViewportState             = &viewportState.stateInfo,
        .pRasterizationState        = &rasterization,
        .pMultisampleState          = &multisampling,
        .pDepthStencilState         = &depthStencil,
        .pColorBlendState           = &blendState.stateInfo,
        .pDynamicState              = nullptr,
        .layout                     = layout,
        .renderPass                 = renderPass.renderPass,
        .subpass                    = 0,
        .basePipelineHandle         = VK_NULL_HANDLE,
        .basePipelineIndex          = -1
    };

     VkCheck(vkCreateGraphicsPipelines(g_devicePtr, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline));
}

////////////////////////////////////////////////////////////

void Pipeline::Destroy()
{
    vkDestroyPipeline(g_devicePtr, pipeline, nullptr);
    vkDestroyPipelineLayout(g_devicePtr, layout, nullptr);
}

////////////////////////////////////////////////////////////

}//ns