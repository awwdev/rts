#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "res/Resources.hpp"
#include "gpu/RenderDataPost.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class PostUniformEnum : u32
{
    OffscreenSampler,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UniformsPost
{
    using RD = RenderDataPost;
    UniformInfo infos [enum_cast(PostUniformEnum::ENUM_END)];
    PushConstants<RD::PushConstants, VK_SHADER_STAGE_VERTEX_BIT> ctx;
    VkSampler sampler; 
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&, SwapResource<Image>&);
    void Destroy();
    void Update(RenderDataPost&, u32);
};

///////////////////////////////////////////////////////////

void UniformsPost::Create(VkCommandPool cmdPool, res::Resources& resources, SwapResource<Image>& spritesOffscreen)
{
    CreateSamplerNearest(sampler);

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
    };
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[enum_cast(PostUniformEnum::OffscreenSampler)].imageInfos.Append(
            sampler,
            spritesOffscreen[i].view,
            spritesOffscreen[i].layout
        );
    }

    descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UniformsPost::Update(RenderDataPost& rd, u32)
{
    ctx.data.windowWidth  = app::Inputs::window.width;
    ctx.data.windowHeight = app::Inputs::window.height;
}

///////////////////////////////////////////////////////////

void UniformsPost::Destroy()
{
    FOR_C_ARRAY(infos, i) infos[i].Destroy();
    descriptors.Destroy();
    vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns