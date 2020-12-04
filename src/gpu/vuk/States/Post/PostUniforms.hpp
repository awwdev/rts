#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"
#include "gpu/RenderData.hpp"
#include "app/Global.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class PostUniformEnum : u32
{
    OffscreenSampler,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct PostUniforms
{
    UniformInfo infos [enum_cast(PostUniformEnum::ENUM_END)];
    PushConstants<PostPushConstants> pushConstants;
    VkSampler sampler; 
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&, Image&);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void PostUniforms::Create(VkCommandPool cmdPool, res::Resources& resources, Image& defaultOffscreen)
{
    CreateSamplerPixelPerfect(sampler);

    infos[enum_cast(PostUniformEnum::OffscreenSampler)] =
    {
        .type = UniformInfo::Image,
        .binding 
        {
            .binding            = enum_cast(PostUniformEnum::OffscreenSampler),
            .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount    = 1,
            .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
            .pImmutableSamplers = nullptr,
        },
        .imageInfo 
        {
            .sampler        = sampler,
            .imageView      = defaultOffscreen.view,
            .imageLayout    = defaultOffscreen.layout,
        }
    };

    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void PostUniforms::Update(RenderData& renderData)
{
}

///////////////////////////////////////////////////////////

void PostUniforms::Destroy()
{
    descriptors.Destroy();
    vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns