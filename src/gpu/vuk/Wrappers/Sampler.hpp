#pragma once

#include "gpu/vuk/Context/Context.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreateSamplerNearest(VkSampler& sampler)
{
    VkSamplerCreateInfo samplerInfo 
    {
        .sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .pNext                   = nullptr,
        .flags                   = 0,
        .magFilter               = VK_FILTER_NEAREST,
        .minFilter               = VK_FILTER_NEAREST, 
        .mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST,
        .addressModeU            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, 
        .addressModeV            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, 
        .addressModeW            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        .mipLodBias              = 0, 
        .anisotropyEnable        = VK_FALSE, 
        .maxAnisotropy           = 0, 
        .compareEnable           = VK_FALSE,
        .compareOp               = VK_COMPARE_OP_ALWAYS, 
        .minLod                  = 0,
        .maxLod                  = 0, 
        .borderColor             = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK, 
        .unnormalizedCoordinates = VK_FALSE
    };
    VkCheck(vkCreateSampler(g_devicePtr, &samplerInfo, nullptr, &sampler));
}

///////////////////////////////////////////////////////////

inline void CreateSamplerLinear(VkSampler& sampler)
{
    VkSamplerCreateInfo samplerInfo 
    {
        .sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .pNext                   = nullptr,
        .flags                   = 0,
        .magFilter               = VK_FILTER_LINEAR,
        .minFilter               = VK_FILTER_LINEAR, 
        .mipmapMode              = VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .addressModeU            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, 
        .addressModeV            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, 
        .addressModeW            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        .mipLodBias              = 0, 
        .anisotropyEnable        = VK_FALSE, 
        .maxAnisotropy           = 0, 
        .compareEnable           = VK_FALSE,
        .compareOp               = VK_COMPARE_OP_ALWAYS, 
        .minLod                  = 0,
        .maxLod                  = 0, 
        .borderColor             = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK, 
        .unnormalizedCoordinates = VK_FALSE
    };
    VkCheck(vkCreateSampler(g_devicePtr, &samplerInfo, nullptr, &sampler));
}

///////////////////////////////////////////////////////////

}//ns