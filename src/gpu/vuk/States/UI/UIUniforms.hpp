#pragma once

#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "app/Global.hpp"
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

struct UIUniforms
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

void UIUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
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

    //? font array
    u32 layerCount = 1; //TODO
    fontArray.Create(cmdPool, VK_FORMAT_R8_SRGB, //grey
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        32, 32, layerCount, true); 

    //TODO store textures
    fontArray.Bake(cmdPool);
    CreateSamplerPixelPerfect(fontArraySampler);

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
        .imageInfo 
        {
            .sampler        = fontArraySampler,
            .imageView      = fontArray.view,
            .imageLayout    = fontArray.layout,
        }
    };

    //? write
    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UIUniforms::Update(RenderDataUI& rd)
{
    metaData.data.windowWidth = app::glo::windowWidth;
    metaData.data.windowHeight = app::glo::windowHeight;

    quadData.count = 0;
    quadData.Append(rd.quadData.data, rd.quadData.count);
}

///////////////////////////////////////////////////////////

void UIUniforms::Destroy()
{
    descriptors.Destroy();
    fontArray.Destroy();
    vkDestroySampler(g_devicePtr, fontArraySampler, GetVkAlloc());
    quadData.Destroy();
}

///////////////////////////////////////////////////////////

}//ns