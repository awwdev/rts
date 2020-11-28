#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/RenderData.hpp"
#include "app/Global.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct DefaultUniforms
{
    PushConstants<DefaultPushConstants> pushConstants;
    VkSampler sampler; 

    void Create();
    void Destroy();
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void DefaultUniforms::Create()
{
    pushConstants.rangeInfo.offset = 0;
    pushConstants.rangeInfo.size = pushConstants.size;
    pushConstants.rangeInfo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    CreateSamplerPixelPerfect(sampler);
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Update(RenderData& renderData)
{
    pushConstants.data.windowWidth = app::glo::windowWidth;
    pushConstants.data.windowHeight = app::glo::windowHeight;
}

///////////////////////////////////////////////////////////

void DefaultUniforms::Destroy()
{
    vkDestroySampler(g_devicePtr, sampler, GetAlloc());
}

///////////////////////////////////////////////////////////

}//ns