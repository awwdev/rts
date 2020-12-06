#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"
#include "gpu/RenderData.hpp"
#include "app/Global.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class UIUniformEnum : u32
{
    FontTextureSampler,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UIUniforms
{
    UniformInfo infos [enum_cast(UIUniformEnum::ENUM_END)];
    VkSampler sampler; 
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void UIUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    CreateSamplerPixelPerfect(sampler);
    /*
    infos[enum_cast(UIUniformEnum::FontTextureSampler)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(UIUniformEnum::FontTextureSampler),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo 
        {
            .sampler        = sampler,
            .imageView      = nullptr,//!
            .imageLayout    = VK_IMAGE_LAYOUT_UNDEFINED,//!
        }
    };

    descriptors.Create(infos);
    */
}

///////////////////////////////////////////////////////////

void UIUniforms::Update(RenderData& renderData)
{
}

///////////////////////////////////////////////////////////

void UIUniforms::Destroy()
{
    //descriptors.Destroy();
    vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns