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
    void Create(VkCommandPool);
    void Destroy();
    void Update(RenderDataWire&, u32);
};

///////////////////////////////////////////////////////////

void UniformsWire::Create(VkCommandPool)
{
}

///////////////////////////////////////////////////////////

void UniformsWire::Update(RenderDataWire& rd, u32)
{
}

///////////////////////////////////////////////////////////

void UniformsWire::Destroy()
{
}

///////////////////////////////////////////////////////////

}//ns