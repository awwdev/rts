#pragma once

#include "gpu/vuk/Wrappers/PushConstants.hpp"
#include "gpu/vuk/Wrappers/BufferExt.hpp"
#include "gpu/vuk/Wrappers/Sampler.hpp"
#include "gpu/vuk/Wrappers/Descriptors.hpp"
#include "gpu/vuk/Wrappers/Image.hpp"

#include "res/Resources.hpp"
#include "gpu/RenderDataWire.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

enum class UniformsEnumWire : u32
{
    ENUM_END
};

///////////////////////////////////////////////////////////

struct UniformsWire
{
    using RD = RenderDataWire;
    PushConstants<RD::PushMeta, VK_SHADER_STAGE_VERTEX_BIT> metaData;

    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderDataWire&);
};

///////////////////////////////////////////////////////////

void UniformsWire::Create(VkCommandPool)
{
}

///////////////////////////////////////////////////////////

void UniformsWire::Update(RenderDataWire& rd)
{
    metaData.data.windowWidth  = app::Inputs::window.width;
    metaData.data.windowHeight = app::Inputs::window.height;
}

///////////////////////////////////////////////////////////

void UniformsWire::Destroy()
{
}

///////////////////////////////////////////////////////////

}//ns