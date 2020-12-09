#pragma once

#include "gpu/vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

template<typename T, VkShaderStageFlags STAGE>
struct PushConstants
{
    static constexpr auto SIZE = sizeof(T);

    T data;
    
    VkPushConstantRange rangeInfo
    {
        .stageFlags = STAGE,
        .offset = 0,
        .size = SIZE,
    };
};

///////////////////////////////////////////////////////////

}//ns