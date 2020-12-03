#pragma once

#include "gpu/vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

template<typename T>
struct PushConstants
{
    T data;
    VkPushConstantRange rangeInfo;
    static constexpr auto size = sizeof(T);
};

///////////////////////////////////////////////////////////

}//ns