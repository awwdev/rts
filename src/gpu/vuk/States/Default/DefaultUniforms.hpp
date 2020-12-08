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

enum class DefaultUniformsEnum : u32
{
    SpriteArray,
    QuadData, 
    ENUM_END
};

///////////////////////////////////////////////////////////

struct DefaultUniforms
{
    using RD = RenderData_Default;

    UniformInfo infos [enum_cast(DefaultUniformsEnum::ENUM_END)];
    Descriptors descriptors;

    PushConstants<RD::Push_Meta> metaData;
    VkSampler spriteArraySampler; 
    Image spriteArray;
    StorageBuffer<RD::Uniform_QuadData, ecs::ENTITY_COUNT_MAX> quadData;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderData_Default&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    //? push
    metaData.rangeInfo.offset = 0;
    metaData.rangeInfo.size = metaData.SIZE;
    metaData.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //? uniform
    quadData.Create();
    infos[enum_cast(DefaultUniformsEnum::QuadData)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(DefaultUniformsEnum::QuadData),
            .descriptorType     = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
        .bufferInfo
        {
            .buffer = quadData.activeBuffer->buffer,
            .offset = 0,
            .range  = VK_WHOLE_SIZE,
        }
    };

    //? texture array
    u32 layerCount = resources.textures.sprites.count;
    spriteArray.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB, 
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        32, 32, layerCount, true); 
    CreateSamplerPixelPerfect(spriteArraySampler);

    auto& textureArrayHost = resources.textures.sprites;
    auto& textureSize = textureArrayHost[0].SIZE;
    spriteArray.Store(cmdPool, textureArrayHost.data, textureSize, textureArrayHost.count); 
    spriteArray.Bake(cmdPool);

    infos[enum_cast(DefaultUniformsEnum::SpriteArray)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(DefaultUniformsEnum::SpriteArray),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo 
        {
            .sampler        = spriteArraySampler,
            .imageView      = spriteArray.view,
            .imageLayout    = spriteArray.layout,
        }
    };

    //? write
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Update(RenderData_Default& rd)
{
    metaData.data.windowWidth  = app::glo::windowWidth;
    metaData.data.windowHeight = app::glo::windowHeight;

    quadData.count = 0;
    quadData.Append(rd.quadData.data, rd.quadData.count);
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Destroy()
{
    descriptors.Destroy();
    spriteArray.Destroy();
    vkDestroySampler(g_devicePtr, spriteArraySampler, GetVkAlloc());
    quadData.Destroy();
}

///////////////////////////////////////////////////////////

}//ns