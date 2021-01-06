#pragma once

#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "res/Resources.hpp"
#include "gpu/RenderDataUI.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct UniformsUI
{
    using RD = RenderDataUI;
    enum : u32
    {
        BindingQuads,
        BindingFont,
        ENUM_END
    };
    UniformInfo infos [ENUM_END];
    Descriptors descriptors;

    PushConstants<RD::PushMeta, VK_SHADER_STAGE_VERTEX_BIT> metaData;
    SwapResource<StorageBuffer<RD::UniformQuadData, RD::QUAD_COUNT_MAX>> quadData;
    VkSampler fontArraySampler; 
    Image fontArray;

    void Create(VkCommandPool, res::Resources&);
    void Update(RenderDataUI&, u32);
    void Destroy();

    void CreateQuads(VkCommandPool, res::Resources&);
    void CreateTexture(VkCommandPool, res::Resources&);
};

///////////////////////////////////////////////////////////

void UniformsUI::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    CreateQuads(cmdPool, resources);
    CreateTexture(cmdPool, resources);
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UniformsUI::CreateQuads(VkCommandPool cmdPool, res::Resources& resources)
{
    auto& info = infos[BindingQuads];
    info.type = UniformInfo::Buffer;
    info.binding.binding = BindingQuads;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    info.binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    quadData.count = g_contextPtr->swapchain.Count();
    FOR_ARRAY(quadData, i)
    {
        quadData[i].Create();
        info.bufferInfos.Append(quadData[i].activeBuffer->buffer, 0u, VK_WHOLE_SIZE);
    }
}

///////////////////////////////////////////////////////////

void UniformsUI::CreateTexture(VkCommandPool cmdPool, res::Resources& resources)
{
    auto& info = infos[BindingFont];
    info.type = UniformInfo::Image;
    info.binding.binding = BindingFont;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    info.binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    auto& textureArray = resources.textures.font;
    auto& texture = textureArray[0];

    fontArray.Create(cmdPool, VK_FORMAT_R8_SRGB,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        texture.WIDTH, texture.HEIGHT, textureArray.count, true); 

    fontArray.Store(cmdPool, textureArray.data, texture.SIZE, textureArray.count); 
    fontArray.Bake(cmdPool);
    CreateSamplerNearest(fontArraySampler);

    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
        info.imageInfos.Append(fontArraySampler, fontArray.view, fontArray.layout);
}

///////////////////////////////////////////////////////////

void UniformsUI::Update(RenderDataUI& rd, u32 swapIdx)
{
    metaData.data.windowWidth  = app::Inputs::window.width;
    metaData.data.windowHeight = app::Inputs::window.height;

    quadData[swapIdx].Clear();
    quadData[swapIdx].Append(rd.quadData.data, rd.quadData.count);
}

///////////////////////////////////////////////////////////

void UniformsUI::Destroy()
{
    FOR_C_ARRAY(infos, i) infos[i].Destroy();
    descriptors.Destroy();
    fontArray.Destroy();
    vkDestroySampler(g_devicePtr, fontArraySampler, GetVkAlloc());
    DestroySwapResource(quadData);
}

///////////////////////////////////////////////////////////

}//ns