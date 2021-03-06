#pragma once

#include "com/Types.hpp"
#include "gpu/vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

auto VertexInput(
VkVertexInputBindingDescription* bindings = nullptr,
u32 bindingCount = 0,
VkVertexInputAttributeDescription* attributes = nullptr,
u32 attributeCount = 0)
{
    return VkPipelineVertexInputStateCreateInfo
    {
        .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .pNext                           = nullptr,
        .flags                           = 0,
        .vertexBindingDescriptionCount   = bindingCount,
        .pVertexBindingDescriptions      = bindings,
        .vertexAttributeDescriptionCount = attributeCount,
        .pVertexAttributeDescriptions    = attributes
    };
}

///////////////////////////////////////////////////////////

inline auto InputAssembly(
VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
VkBool32 restart = VK_FALSE)
{
    return VkPipelineInputAssemblyStateCreateInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .topology               = topology,
        .primitiveRestartEnable = restart 
    };    
}

///////////////////////////////////////////////////////////

struct ViewportStateInfo
{
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo stateInfo;

    ViewportStateInfo() = default;
    ViewportStateInfo(ViewportStateInfo const& other)
    {
        this->operator=(other);
    }
    void operator=(ViewportStateInfo const& other)
    {
        this->viewport = other.viewport;
        this->scissor = other.scissor;
        this->stateInfo = other.stateInfo;
        stateInfo.pViewports = &this->viewport;
        stateInfo.pScissors = &this->scissor;
    }
};

///////////////////////////////////////////////////////////

inline auto ViewportState(uint32_t width, uint32_t height)
{
    ViewportStateInfo stateInfo;

    stateInfo.viewport =
    {
        .x        = 0.f,
        .y        = 0.f,
        .width    = (f32)width,
        .height   = (f32)height,
        .minDepth = 0.f,
        .maxDepth = 1.f
    };

    stateInfo.scissor  =
    {
        .offset = VkOffset2D { 0, 0 },
        .extent = VkExtent2D { width, height }
    };

    stateInfo.stateInfo = 
    {
        .sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .pNext         = nullptr,
        .flags         = 0,
        .viewportCount = 1, 
        .pViewports    = &stateInfo.viewport,
        .scissorCount  = 1,
        .pScissors     = &stateInfo.scissor
    };

    return stateInfo;
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

inline auto Rasterization(
VkPolygonMode mode = VK_POLYGON_MODE_FILL, 
VkCullModeFlags cull = VK_CULL_MODE_NONE,
f32 lineWidth = 1.f)
{
    return VkPipelineRasterizationStateCreateInfo 
    {
        .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .pNext                   = nullptr,
        .flags                   = 0,
        .depthClampEnable        = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode             = mode,
        .cullMode                = cull,
        .frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable         = VK_FALSE,
        .depthBiasConstantFactor = 0.f,
        .depthBiasClamp          = 0.f,
        .depthBiasSlopeFactor    = 0.f,
        .lineWidth               = lineWidth
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

    BlendState() = default;
    BlendState(BlendState const& other)
    {
        this->operator=(other);
    }
    void operator=(BlendState const& other)
    {
        this->attachment = other.attachment;
        this->stateInfo = other.stateInfo;
        stateInfo.pAttachments = &this->attachment;
    }
};

///////////////////////////////////////////////////////////

inline auto BlendStateInfo()
{
    BlendState blendState;

    blendState.attachment =
    {
        .blendEnable          = VK_TRUE,
        .srcColorBlendFactor  = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor  = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, 
        .colorBlendOp         = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor  = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstAlphaBlendFactor  = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .alphaBlendOp         = VK_BLEND_OP_ADD,
        .colorWriteMask       = 
            VK_COLOR_COMPONENT_R_BIT | 
            VK_COLOR_COMPONENT_G_BIT | 
            VK_COLOR_COMPONENT_B_BIT | 
            VK_COLOR_COMPONENT_A_BIT
    };
    
    blendState.stateInfo =
    {
        .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .pNext           = nullptr,
        .flags           = 0,
        .logicOpEnable   = VK_FALSE,
        .logicOp         = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments    = &blendState.attachment,
        .blendConstants  = { 0.f, 0.f, 0.f, 0.f }
    };

    return blendState;
}

///////////////////////////////////////////////////////////

inline auto PipelineLayout(
VkDescriptorSetLayout* setLayouts = nullptr, 
u32 setLayoutCount = 0,
VkPushConstantRange* pushConstantRanges = nullptr,
u32 pushConstantCount = 0)
{
    return VkPipelineLayoutCreateInfo
    {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .setLayoutCount         = setLayoutCount,
        .pSetLayouts            = setLayouts,
        .pushConstantRangeCount = pushConstantCount,
        .pPushConstantRanges    = pushConstantRanges,
    };
}

///////////////////////////////////////////////////////////

struct PipelineInfo
{
    VkPipelineVertexInputStateCreateInfo vertexInput;
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    ViewportStateInfo viewportState;
    VkPipelineMultisampleStateCreateInfo multisampling;
    VkPipelineRasterizationStateCreateInfo rasterization;
    VkPipelineDepthStencilStateCreateInfo depthStencil;
    BlendState blendState;
    VkPipelineLayoutCreateInfo layoutInfo;
};

///////////////////////////////////////////////////////////

}//ns