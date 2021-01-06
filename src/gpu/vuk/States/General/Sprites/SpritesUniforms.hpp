#pragma once

#include "gpu/vuk/Wrappers/SwapResource.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"
#include "gpu/vuk/States/General/GeneralRenderPass.hpp"
#include "gpu/vuk/States/General/Shadow/ShadowRenderPass.hpp"

#include "app/Input/Inputs.hpp"
#include "res/Resources.hpp"
#include "gpu/RenderDataSprites.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct UniformsSprites
{
    using RD = RenderDataSprites;
    enum : u32
    {
        BindingQuads, 
        BindingMeta,
        BindingSun,
        BindingSprites,
        BindingShadowOffscreen,
        ENUM_END
    };
    UniformInfo infos [ENUM_END];
    Descriptors descriptors;

    PushConstants<RD::PushContext, VK_SHADER_STAGE_VERTEX_BIT> ctx;
    SwapResource<StorageBuffer<RD::UniformQuad, ecs::ENTITY_COUNT_MAX>> quads;
    SwapResource<UniformBuffer<RD::UniformSun, 1>> sun;
    SwapResource<UniformBuffer<RD::UniformMeta, 1>> meta;
    VkSampler shadowOffscreenSampler;
    VkSampler spriteArraySampler; 
    Image spriteArray;

    void Create               (VkCommandPool, res::Resources&, RenderPassShadow&);
    void CreateQuads          (VkCommandPool, res::Resources&, RenderPassShadow&);
    void CreateSun            (VkCommandPool, res::Resources&, RenderPassShadow&);
    void CreateMeta           (VkCommandPool, res::Resources&, RenderPassShadow&);
    void CreateShadowTexture  (VkCommandPool, res::Resources&, RenderPassShadow&);
    void CreateSpritesTexture (VkCommandPool, res::Resources&, RenderPassShadow&);
    
    void Update(RenderDataSprites&, u32);
    void Destroy();
};

///////////////////////////////////////////////////////////

void UniformsSprites::CreateQuads(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    auto& info = infos[BindingQuads];
    info.type = UniformInfo::Buffer;
    info.binding.binding = BindingQuads;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    info.binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    quads.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(quads, i)
        quads[i].Create();
    FOR_ARRAY(quads, i)
        info.bufferInfos.Append(quads[i].activeBuffer->buffer, 0u, VK_WHOLE_SIZE);   
}

///////////////////////////////////////////////////////////

void UniformsSprites::CreateSun(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    auto& info = infos[BindingSun];
    info.type = UniformInfo::Buffer;
    info.binding.binding = BindingSun;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    info.binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    sun.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(sun, i)
        sun[i].Create();
    FOR_ARRAY(quads, i)
        info.bufferInfos.Append(sun[i].activeBuffer->buffer, 0u, VK_WHOLE_SIZE);   
}

///////////////////////////////////////////////////////////

void UniformsSprites::CreateMeta(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    auto& info = infos[BindingMeta];
    info.type = UniformInfo::Buffer;
    info.binding.binding = BindingMeta;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    info.binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    meta.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(meta, i)
        meta[i].Create();
    FOR_ARRAY(quads, i)
        info.bufferInfos.Append(meta[i].activeBuffer->buffer, 0u, VK_WHOLE_SIZE);  
}

///////////////////////////////////////////////////////////

void UniformsSprites::CreateShadowTexture(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    auto& info = infos[BindingShadowOffscreen];
    info.type = UniformInfo::Image;
    info.binding.binding = BindingShadowOffscreen;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    info.binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    CreateSamplerNearest(shadowOffscreenSampler);
    FOR_ARRAY(quads, i)
        info.imageInfos.Append(shadowOffscreenSampler, shadowPass.image.view, shadowPass.image.layout);  
}

///////////////////////////////////////////////////////////

void UniformsSprites::CreateSpritesTexture(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    auto& info = infos[BindingSprites];
    info.type = UniformInfo::Image;
    info.binding.binding = BindingSprites;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    info.binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    auto& textureArray = resources.textures.sprites;
    auto& texture = textureArray[0];

    spriteArray.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        texture.WIDTH, texture.HEIGHT, textureArray.count, true); 
    spriteArray.Store(cmdPool, textureArray.data, texture.SIZE, textureArray.count); 
    spriteArray.Bake(cmdPool);

    CreateSamplerNearest(spriteArraySampler);
    FOR_ARRAY(quads, i)
        info.imageInfos.Append(spriteArraySampler, spriteArray.view, spriteArray.layout);  
}

///////////////////////////////////////////////////////////

void UniformsSprites::Create(VkCommandPool cmdPool, res::Resources& resources, RenderPassShadow& shadowPass)
{
    CreateQuads         (cmdPool, resources, shadowPass);
    CreateSun           (cmdPool, resources, shadowPass);
    CreateMeta          (cmdPool, resources, shadowPass);
    CreateShadowTexture (cmdPool, resources, shadowPass);
    CreateSpritesTexture(cmdPool, resources, shadowPass);
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UniformsSprites::Update(RenderDataSprites& rd, u32 swapIdx)
{
    ctx.data.windowWidth  = app::Inputs::window.width;
    ctx.data.windowHeight = app::Inputs::window.height;
    meta[swapIdx].Clear();
    meta[swapIdx].Append(RD::UniformMeta {rd.meta.cameraPos});
    sun[swapIdx].Clear();
    sun[swapIdx].Append(rd.sun);
    quads[swapIdx].Clear();
    quads[swapIdx].Append(rd.quads.data, rd.quads.count);
}

///////////////////////////////////////////////////////////

void UniformsSprites::Destroy()
{
    FOR_C_ARRAY(infos, i) infos[i].Destroy();
    descriptors.Destroy();
    spriteArray.Destroy();
    vkDestroySampler(g_devicePtr, spriteArraySampler, GetVkAlloc());
    vkDestroySampler(g_devicePtr, shadowOffscreenSampler, GetVkAlloc());
    DestroySwapResource(quads);
    DestroySwapResource(meta);
    DestroySwapResource(sun);
}

///////////////////////////////////////////////////////////

}//ns