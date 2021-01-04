#pragma once

#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"
#include "gpu/vuk/States/Sprites/SpritesRenderPass.hpp"
#include "gpu/vuk/States/Sprites/ShadowRenderPass.hpp"

#include "app/Inputs.hpp"
#include "res/Resources.hpp"
#include "gpu/RenderDataSprites.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class UniformEnumSprites : u32
{
    Quads, 
    Meta,
    Sun,
    Sprites,
    ShadowOffscreen,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UniformsSprites
{
    using RD = RenderDataSprites;

    UniformInfo infos [enum_cast(UniformEnumSprites::ENUM_END)];
    Descriptors descriptors;

    PushConstants<RD::PushContext, VK_SHADER_STAGE_VERTEX_BIT> ctx;
    VkSampler spriteArraySampler; 
    Image spriteArray;
    SwapResource<StorageBuffer<RD::UniformQuad, ecs::ENTITY_COUNT_MAX>> quads;
    SwapResource<UniformBuffer<RD::UniformMeta, 1>> meta;
    UniformBuffer<RD::UniformSun, 1> sun;
    VkSampler shadowOffscreenSampler;
    
    void Create(VkCommandPool, res::Resources&, RenderPassShadow&);
    void Destroy();
    void Update(RenderDataSprites&, u32);
};

///////////////////////////////////////////////////////////

void UniformsSprites::Create(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    //? QUADS
    quads.count = 4;
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
        quads[i].Create();
    infos[enum_cast(UniformEnumSprites::Quads)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(UniformEnumSprites::Quads),
            .descriptorType     = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UniformEnumSprites::Quads)].bufferInfos.Append(
            quads[i].activeBuffer->buffer,
            0u,
            VK_WHOLE_SIZE
        );
    }

    //? SHADOW
    sun.Create();
    infos[enum_cast(UniformEnumSprites::Sun)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(UniformEnumSprites::Sun),
            .descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UniformEnumSprites::Sun)].bufferInfos.Append(
            sun.activeBuffer->buffer,
            0u,
            VK_WHOLE_SIZE
        );
    }

    //? META
    meta.count = 4;
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
        meta[i].Create();
    infos[enum_cast(UniformEnumSprites::Meta)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(UniformEnumSprites::Meta),
            .descriptorType     = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UniformEnumSprites::Meta)].bufferInfos.Append(
            meta[i].activeBuffer->buffer,
            0u,
            VK_WHOLE_SIZE
        );
    }

    //? SAMPLER
    CreateSamplerNearest(shadowOffscreenSampler);
    infos[enum_cast(UniformEnumSprites::ShadowOffscreen)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(UniformEnumSprites::ShadowOffscreen),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UniformEnumSprites::ShadowOffscreen)].imageInfos.Append(
            shadowOffscreenSampler,
            shadowPass.image.view,
            shadowPass.image.layout
        );
    }

    //?SPRITES
    auto& textureArray = resources.textures.sprites;
    auto& texture = textureArray[0];

    spriteArray.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        texture.WIDTH, texture.HEIGHT, textureArray.count, true); 

    spriteArray.Store(cmdPool, textureArray.data, texture.SIZE, textureArray.count); 
    spriteArray.Bake(cmdPool);
    CreateSamplerNearest(spriteArraySampler);

    infos[enum_cast(UniformEnumSprites::Sprites)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(UniformEnumSprites::Sprites),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UniformEnumSprites::Sprites)].imageInfos.Append(
            spriteArraySampler,
            spriteArray.view,
            spriteArray.layout
        );
    }

    //? write
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UniformsSprites::Update(RenderDataSprites& rd, u32 imageIndex)
{
    ctx.data.windowWidth  = app::Inputs::window.width;
    ctx.data.windowHeight = app::Inputs::window.height;
    meta[imageIndex].Clear();
    meta[imageIndex].Append(RD::UniformMeta {rd.meta.cameraPos});
    sun.Clear();
    sun.Append(rd.sun);
    quads[imageIndex].Clear();
    quads[imageIndex].Append(rd.quads.data, rd.quads.count);
}

///////////////////////////////////////////////////////////

void UniformsSprites::Destroy()
{
    descriptors.Destroy();
    spriteArray.Destroy();
    vkDestroySampler(g_devicePtr, spriteArraySampler, GetVkAlloc());
    vkDestroySampler(g_devicePtr, shadowOffscreenSampler, GetVkAlloc());
    DestroySwapResource(quads);
    DestroySwapResource(meta);
    sun.Destroy();
}

///////////////////////////////////////////////////////////

}//ns