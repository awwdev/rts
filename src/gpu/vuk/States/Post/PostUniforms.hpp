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

struct UniformsPost
{
    using RD = RenderDataPost;
    enum : u32
    {
        BindingOffscreen,
        ENUM_END
    };
    UniformInfo infos [ENUM_END];
    Descriptors descriptors;

    PushConstants<RD::PushConstants, VK_SHADER_STAGE_VERTEX_BIT> ctx;
    VkSampler sampler; 

    void Create(VkCommandPool, res::Resources&, SwapResource<Image>&);
    void Update(RenderDataPost&, u32);
    void Destroy();
};

///////////////////////////////////////////////////////////

void UniformsPost::Create(VkCommandPool cmdPool, res::Resources& resources, SwapResource<Image>& spritesOffscreen)
{
    //offscreen from general state
    auto& info = infos[BindingOffscreen];
    info.type = UniformInfo::Image;
    info.binding.binding = BindingOffscreen;
    info.binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    info.binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    CreateSamplerNearest(sampler);
    for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
    {
        infos[BindingOffscreen].imageInfos.Append(
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
    vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
    descriptors.Destroy();
}

///////////////////////////////////////////////////////////

}//ns