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
    Image textureArray;
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    //push constants
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //textures
    u32 layerCount = resources.textures.textureArray.count;
    textureArray.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB, 
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        32, 32, layerCount); 
    textureArray.Transition(
        cmdPool, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 
        0, VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT
    );
    CreateSamplerPixelPerfect(sampler);

    //store
    auto& textureArrayHost = resources.textures.textureArray;
    auto& textureSize  = textureArrayHost[0].SIZE;
    textureArray.Store(cmdPool, textureArrayHost.data, textureSize * textureArrayHost.count, textureSize); 
    //TODO textureArray class ? 
    //TODO count instead of total size
    textureArray.Bake(cmdPool);

    infos[enum_cast(DefaultUniformEnum::TextureSampler)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(DefaultUniformEnum::TextureSampler),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo 
        {
            .sampler        = sampler,
            .imageView      = textureArray.view,
            .imageLayout    = textureArray.layout,
        }
    };

    //descriptors
    descriptors.Create(infos);
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
    descriptors.Destroy();
    textureArray.Destroy();
    vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns