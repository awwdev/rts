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
    TextureSampler,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct PostUniforms
{
    UniformInfo infos [enum_cast(PostUniformEnum::ENUM_END)];
    PushConstants<PostPushConstants> pushConstants;
    VkSampler sampler; 
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void PostUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
}

///////////////////////////////////////////////////////////

void PostUniforms::Update(RenderData& renderData)
{
}

///////////////////////////////////////////////////////////

void PostUniforms::Destroy()
{
}

///////////////////////////////////////////////////////////

}//ns