#pragma once

#include "gpu/vuk/Wrappers/RenderPass.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

inline void CreateDefaultRenderPass(RenderPass& renderPass, Swapchain& swapchain)
{
    renderPass.clear = { .color { 0.025, 0.025, 0.025, 1 } };
    renderPass.Create(swapchain);
}

///////////////////////////////////////////////////////////

}//ns