#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "ecs/EntityID.hpp"
#include "app/Global.hpp"
#include "res/Resources.hpp"
#include "gpu/RenderDataDefault.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class DefaultUniformEnum : u32
{
    TextureArray,
    UBO, 
    ENUM_END
};

///////////////////////////////////////////////////////////

struct DefaultUniforms
{
    UniformInfo infos [enum_cast(DefaultUniformEnum::ENUM_END)];
    Descriptors descriptors;

    PushConstants<PushConstantsDefault> pushConstants;
    VkSampler textureArraySampler; 
    Image textureArray;
    StorageBuffer<UniformDefault, ecs::ENTITY_COUNT_MAX> ubo;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderDataDefault&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    //push constants
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //uniform
    ubo.Create();

    infos[enum_cast(DefaultUniformEnum::UBO)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(DefaultUniformEnum::UBO),
            .descriptorType     = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
        .bufferInfo
        {
            .buffer = ubo.activeBuffer->buffer,
            .offset = 0,
            .range = VK_WHOLE_SIZE,
        }
    };

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
    CreateSamplerPixelPerfect(textureArraySampler);

    //store
    auto& textureArrayHost = resources.textures.textureArray;
    auto& textureSize  = textureArrayHost[0].SIZE;
    textureArray.Store(cmdPool, textureArrayHost.data, textureSize * textureArrayHost.count, textureSize); 
    textureArray.Bake(cmdPool);

    infos[enum_cast(DefaultUniformEnum::TextureArray)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(DefaultUniformEnum::TextureArray),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo 
        {
            .sampler        = textureArraySampler,
            .imageView      = textureArray.view,
            .imageLayout    = textureArray.layout,
        }
    };

    //write
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Update(RenderDataDefault& rd)
{
    pushConstants.data.windowWidth = app::glo::windowWidth;
    pushConstants.data.windowHeight = app::glo::windowHeight;

    ubo.count = 0;
    ubo.Append(rd.ubo.data, rd.ubo.count);
    //!does not really store data
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Destroy()
{
    descriptors.Destroy();
    textureArray.Destroy();
    vkDestroySampler(g_devicePtr, textureArraySampler, GetVkAlloc());
    ubo.Destroy();
}

///////////////////////////////////////////////////////////

}//ns