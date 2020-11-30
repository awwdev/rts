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
    Image textures;

    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create(VkCommandPool cmdPool)
{
    //push constants
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //textures
    textures.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB, 
    VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 32, 32, 1);
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
            .imageView      = textures.view,
            .imageLayout    = textures.layout,
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
    textures.Destroy();
}

///////////////////////////////////////////////////////////

}//ns