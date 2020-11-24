#pragma once

#include "vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

inline VkCommandBufferBeginInfo CreateCmdBeginInfo(VkCommandBufferUsageFlags flags = 0)
{
    return {
        .sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext            = nullptr,
        .flags            = flags,
        .pInheritanceInfo = nullptr
    };
}

////////////////////////////////////////////////////////////

}//ns