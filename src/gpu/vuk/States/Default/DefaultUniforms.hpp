#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"
#include "gpu/RenderData.hpp"
#include "app/Global.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

enum class DefaultUniformEnum : u32
{
    TextureSampler,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct DefaultUniforms
{
    UniformInfo infos [enum_cast(DefaultUniformEnum::ENUM_END)];
    PushConstants<DefaultPushConstants> pushConstants;
    VkSampler sampler; 

    void Create();
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create()
{
    //push constants
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //sampler
    CreateSamplerPixelPerfect(sampler);
    infos[enum_cast(DefaultUniformEnum::TextureSampler)] =
    {
        .type = UniformInfo::Image,
        .binding {
            .binding            = enum_cast(DefaultUniformEnum::TextureSampler),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo {
            .sampler        = sampler,
            .imageView      = 0,//!finalImage.view,
            .imageLayout    = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,//!finalImage.currentLayout
        }
    };
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Update(RenderData& renderData)
{
    pushConstants.data.windowWidth = app::glo::windowWidth;
    pushConstants.data.windowHeight = app::glo::windowHeight;
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Destroy()
{
    vkDestroySampler(g_devicePtr, sampler, GetAlloc());
}

///////////////////////////////////////////////////////////

}//ns