#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "app/Global.hpp"
#include "res/Resources.hpp"
#include "gpu/RenderDataUI.hpp"

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
    PushConstants<PushConstantsUI> pushConstants;
    VkSampler sampler; 
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderDataUI&);
};

///////////////////////////////////////////////////////////

void UIUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    CreateSamplerPixelPerfect(sampler);

    //push constants
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //TODO font texture
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

void UIUniforms::Update(RenderDataUI& rd)
{
    pushConstants.data.windowWidth = app::glo::windowWidth;
    pushConstants.data.windowHeight = app::glo::windowHeight;
}

///////////////////////////////////////////////////////////

void UIUniforms::Destroy()
{
    //descriptors.Destroy();
    vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns