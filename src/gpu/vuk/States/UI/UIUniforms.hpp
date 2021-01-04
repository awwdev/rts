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

enum class UIUniformsEnum : u32
{
    QuadData,
    FontArray,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UniformsUI
{
    using RD = RenderDataUI;

    UniformInfo infos [enum_cast(UIUniformsEnum::ENUM_END)];
    Descriptors descriptors;

    PushConstants<RD::PushMeta, VK_SHADER_STAGE_VERTEX_BIT> metaData;
    VkSampler fontArraySampler; 
    Image fontArray;
    StorageBuffer<RD::UniformQuadData, RD::QUAD_COUNT_MAX> quadData;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderDataUI&);
};

///////////////////////////////////////////////////////////

void UniformsUI::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    //? uniform
    quadData.Create();
    infos[enum_cast(UIUniformsEnum::QuadData)] =
    {
        .type = UniformInfo::Buffer,
        .binding 
        {
            .binding            = enum_cast(UIUniformsEnum::QuadData),
            .descriptorType     = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_VERTEX_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UIUniformsEnum::QuadData)].bufferInfos.Append(
            quadData.activeBuffer->buffer,
            0u,
            VK_WHOLE_SIZE
        );
    }

    //? font array
    auto& textureArray = resources.textures.font;
    auto& texture = textureArray[0];

    fontArray.Create(cmdPool, VK_FORMAT_R8_SRGB,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        texture.WIDTH, texture.HEIGHT, textureArray.count, true); 

    fontArray.Store(cmdPool, textureArray.data, texture.SIZE, textureArray.count); 
    fontArray.Bake(cmdPool);
    CreateSamplerNearest(fontArraySampler);

    infos[enum_cast(UIUniformsEnum::FontArray)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(UIUniformsEnum::FontArray),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(UIUniformsEnum::FontArray)].imageInfos.Append(
            fontArraySampler,
            fontArray.view,
            fontArray.layout
        );
    }

    //? write
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UniformsUI::Update(RenderDataUI& rd)
{
    metaData.data.windowWidth  = app::Inputs::window.width;
    metaData.data.windowHeight = app::Inputs::window.height;

    quadData.Clear();
    quadData.Append(rd.quadData.data, rd.quadData.count);
}

///////////////////////////////////////////////////////////

void UniformsUI::Destroy()
{
    descriptors.Destroy();
    fontArray.Destroy();
    vkDestroySampler(g_devicePtr, fontArraySampler, GetVkAlloc());
    quadData.Destroy();
}

///////////////////////////////////////////////////////////

}//ns