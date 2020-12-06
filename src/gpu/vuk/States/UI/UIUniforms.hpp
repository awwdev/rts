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

enum class UIUniformEnum : u32
{
    None,
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UIUniforms
{
    UniformInfo infos [enum_cast(UIUniformEnum::ENUM_END)];
    PushConstants<PushConstantsPost> pushConstants;
    VkSampler sampler; 
    Descriptors descriptors;

    void Create(VkCommandPool, res::Resources&);
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void UIUniforms::Create(VkCommandPool cmdPool, res::Resources& resources)
{
    CreateSamplerPixelPerfect(sampler);
    //descriptors.Create(infos);
}

///////////////////////////////////////////////////////////

void UIUniforms::Update(RenderData& renderData)
{
}

///////////////////////////////////////////////////////////

void UIUniforms::Destroy()
{
    //descriptors.Destroy();
    //vkDestroySampler(g_devicePtr, sampler, GetVkAlloc());
}

///////////////////////////////////////////////////////////

}//ns