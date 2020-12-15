#pragma once

#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "app/Input/Input.hpp"
#include "res/Resources.hpp"
#include "gpu/RenderDataDefault.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class DefaultUniformsEnum : u32
{
    QuadData, 
    SpriteArray,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct DefaultUniforms
{
    using RD = RenderDataDefault;

    UniformInfo infos [enum_cast(DefaultUniformsEnum::ENUM_END)];
    Descriptors descriptors;

    PushConstants<RD::PushMeta, VK_SHADER_STAGE_VERTEX_BIT> metaData;
    VkSampler spriteArraySampler; 
    Image spriteArray;
    StorageBuffer<RD::UniformQuadData, ecs::ENTITY_COUNT_MAX> quadData;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderDataDefault&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
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
    auto& textureArray = resources.textures.sprites;
    auto& texture = textureArray[0];

    spriteArray.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        texture.WIDTH, texture.HEIGHT, textureArray.count, true); 

    spriteArray.Store(cmdPool, textureArray.data, texture.SIZE, textureArray.count); 
    spriteArray.Bake(cmdPool);
    CreateSamplerNearest(spriteArraySampler);

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

void DefaultUniforms::Update(RenderDataDefault& rd)
{
    metaData.data.windowWidth  = app::Inputs::window.width;
    metaData.data.windowHeight = app::Inputs::window.height;

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