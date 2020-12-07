#pragma once

#include "gpu/vuk/Vulkan.hpp"
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

enum class UIUniformEnum : u32
{
    TextureArray,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UIUniforms
{
    UniformInfo infos [enum_cast(UIUniformEnum::ENUM_END)];
    Descriptors descriptors;

    PushConstants<PushConstantsUI> pushConstants;
    VkSampler textureArraySampler; 
    Image textureArray;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderDataUI&);
};

///////////////////////////////////////////////////////////

void UIUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    //push constants
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    //font texture
    textureArray.Create(cmdPool, VK_FORMAT_R8G8B8A8_SRGB, 
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, 
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,
        32, 32, 1); 
    textureArray.Transition(
        cmdPool, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 
        0, VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT
    );
    textureArray.Bake(cmdPool);
    CreateSamplerPixelPerfect(textureArraySampler);

    infos[enum_cast(UIUniformEnum::TextureArray)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(UIUniformEnum::TextureArray),
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

void UIUniforms::Update(RenderDataUI& rd)
{
    pushConstants.data.windowWidth = app::glo::windowWidth;
    pushConstants.data.windowHeight = app::glo::windowHeight;
}

///////////////////////////////////////////////////////////

void UIUniforms::Destroy()
{
    descriptors.Destroy();
    textureArray.Destroy();
    vkDestroySampler(g_devicePtr, textureArraySampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns