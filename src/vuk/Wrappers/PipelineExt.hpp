#pragma once

#include "com/Types.hpp"
#include "vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

inline auto VertexInput()
{
    return VkPipelineVertexInputStateCreateInfo
    {
        .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .pNext                           = nullptr,
        .flags                           = 0,
        .vertexBindingDescriptionCount   = 0,
        .pVertexBindingDescriptions      = nullptr,
        .vertexAttributeDescriptionCount = 0,
        .pVertexAttributeDescriptions    = nullptr
    };
}

///////////////////////////////////////////////////////////

inline auto InputAssembly()
{
    return VkPipelineInputAssemblyStateCreateInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE 
    };    
}

///////////////////////////////////////////////////////////

struct ViewportStateInfo
{
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo stateInfo;
};

///////////////////////////////////////////////////////////

inline auto ViewportState(uint32_t width, uint32_t height)
{
    VkViewport viewport
    {
        .x        = 0.f,
        .y        = 0.f,
        .width    = (f32)width,
        .height   = (f32)height,
        .minDepth = 0.f,
        .maxDepth = 1.f
    };

    VkRect2D scissor 
    {
        .offset = VkOffset2D { 0, 0 },
        .extent = VkExtent2D { 
            width,
            height 
        }
    };

    VkPipelineViewportStateCreateInfo stateInfo
    {
        .sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .pNext         = nullptr,
        .flags         = 0,
        .viewportCount = 1, 
        .pViewports    = &viewport,
        .scissorCount  = 1,
        .pScissors     = &scissor
    };

    return ViewportStateInfo { viewport, scissor, stateInfo };
}

///////////////////////////////////////////////////////////

inline auto Multisampling()
{
    return VkPipelineMultisampleStateCreateInfo
    {
        .sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .pNext                 = nullptr,
        .flags                 = 0,
        .rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable   = VK_FALSE,
        .minSampleShading      = 1.f,
        .pSampleMask           = nullptr,
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable      = VK_FALSE
    };
}

///////////////////////////////////////////////////////////

inline auto Rasterization()
{
    return VkPipelineRasterizationStateCreateInfo 
    {
        .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .pNext                   = nullptr,
        .flags                   = 0,
        .depthClampEnable        = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode             = VK_POLYGON_MODE_FILL,
        .cullMode                = VK_CULL_MODE_BACK_BIT,
        .frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable         = VK_FALSE,
        .depthBiasConstantFactor = 0.f,
        .depthBiasClamp          = 0.f,
        .depthBiasSlopeFactor    = 0.f,
        .lineWidth               = 1.f
    };
}

///////////////////////////////////////////////////////////

inline auto DepthStencil()
{
    return VkPipelineDepthStencilStateCreateInfo
    {
        .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .pNext                 = nullptr,
        .flags                 = 0,
        .depthTestEnable       = VK_FALSE,
        .depthWriteEnable      = VK_FALSE,
        .depthCompareOp        = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable     = VK_FALSE,
        .front                 = {},
        .back                  = {},
        .minDepthBounds        = 0.f,
        .maxDepthBounds        = 1.f
    };  
}

///////////////////////////////////////////////////////////

struct BlendState
{
    VkPipelineColorBlendAttachmentState attachment;
    VkPipelineColorBlendStateCreateInfo stateInfo;
};

///////////////////////////////////////////////////////////

inline auto BlendStateInfo()
{
    VkPipelineColorBlendAttachmentState blendAttachment
    {
        .blendEnable                = VK_TRUE,
        .srcColorBlendFactor        = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor        = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, 
        .colorBlendOp               = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor        = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor        = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp               = VK_BLEND_OP_ADD,
        .colorWriteMask             = 
            VK_COLOR_COMPONENT_R_BIT | 
            VK_COLOR_COMPONENT_G_BIT | 
            VK_COLOR_COMPONENT_B_BIT | 
            VK_COLOR_COMPONENT_A_BIT
    };
    
    VkPipelineColorBlendStateCreateInfo blendState
    {
        .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .pNext           = nullptr,
        .flags           = 0,
        .logicOpEnable   = VK_FALSE,
        .logicOp         = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments    = &blendAttachment,
        .blendConstants  = { 0.f, 0.f, 0.f, 0.f }
    };

    return BlendState { blendAttachment, blendState };
}

////////////////////////////////////////////////////////////

inline auto PipelineLayout()
{
    return VkPipelineLayoutCreateInfo
    {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .setLayoutCount         = 0,
        .pSetLayouts            = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges    = nullptr,
    };
}

///////////////////////////////////////////////////////////

}//ns