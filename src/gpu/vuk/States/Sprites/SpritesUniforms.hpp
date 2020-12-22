#pragma once

#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"
#include "gpu/vuk/States/Sprites/SpritesRenderPass.hpp"

#include "app/Inputs.hpp"
#include "res/Resources.hpp"
#include "gpu/RenderDataSprites.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class SpritesUniformsEnum : u32
{
    QuadData, 
    SpriteArray,
    ShadowData,
    ShadowOffscreen,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct SpritesUniforms
{
    using RD = RenderDataSprites;

    UniformInfo infos [enum_cast(SpritesUniformsEnum::ENUM_END)];
    Descriptors descriptors;

    PushConstants<RD::PushMeta, VK_SHADER_STAGE_VERTEX_BIT> metaData;
    VkSampler spriteArraySampler; 
    Image spriteArray;
    StorageBuffer<RD::UniformQuadData, ecs::ENTITY_COUNT_MAX> quadData;
    UniformBuffer<RD::UniformShadowData, 1> shadowData;
    VkSampler shadowOffscreenSampler;
    
    void Create(VkCommandPool, res::Resources&, SpritesRenderPass&);
    void Destroy();
    void Update(RenderDataSprites&);
};

///////////////////////////////////////////////////////////

void SpritesUniforms::Create(VkCommandPool cmdPool, res::Resources& resources, SpritesRenderPass& renderPass)
{
    //? uniform
    quadData.Create();
    infos[enum_cast(SpritesUniformsEnum::QuadData)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(SpritesUniformsEnum::QuadData),
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

    //? uniform
    shadowData.Create();
    infos[enum_cast(SpritesUniformsEnum::ShadowData)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(SpritesUniformsEnum::ShadowData),
            .descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
        .bufferInfo
        {
            .buffer = shadowData.activeBuffer->buffer,
            .offset = 0,
            .range  = VK_WHOLE_SIZE,
        }
    };

    CreateSamplerNearest(shadowOffscreenSampler);
    infos[enum_cast(SpritesUniformsEnum::ShadowOffscreen)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(SpritesUniformsEnum::ShadowOffscreen),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo 
        {
            .sampler        = shadowOffscreenSampler,
            .imageView      = renderPass.shadows.view,
            .imageLayout    = renderPass.shadows.layout,
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

    infos[enum_cast(SpritesUniformsEnum::SpriteArray)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(SpritesUniformsEnum::SpriteArray),
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

void SpritesUniforms::Update(RenderDataSprites& rd)
{
    metaData.data.windowWidth  = app::Inputs::window.width;
    metaData.data.windowHeight = app::Inputs::window.height;

    shadowData.Clear();
    shadowData.Append(rd.shadowData);
    quadData.Clear();
    quadData.Append(rd.quadData.data, rd.quadData.count);
}

///////////////////////////////////////////////////////////

void SpritesUniforms::Destroy()
{
    descriptors.Destroy();
    spriteArray.Destroy();
    vkDestroySampler(g_devicePtr, spriteArraySampler, GetVkAlloc());
    vkDestroySampler(g_devicePtr, shadowOffscreenSampler, GetVkAlloc());
    quadData.Destroy();
    shadowData.Destroy();
}

///////////////////////////////////////////////////////////

}//ns