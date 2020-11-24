#pragma once

#include "vuk/Vulkan.hpp"
#include "com/SimpleArray.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

////////////////////////////////////////////////////////////

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
VkDebugUtilsMessageTypeFlagsEXT,
const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
void*)
{
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        com::PrintWarning(pCallbackData->pMessage);
    }
        
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
    {
        com::PrintError(pCallbackData->pMessage);
        __builtin_trap();
    }

    return VK_FALSE;
}

///////////////////////////////////////////////////////////

VkDebugUtilsMessengerCreateInfoEXT 
Instance::DebugInfo()
{
    return 
    {
        .sType                  = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext                  = nullptr,
        .flags                  = 0,
        .messageSeverity        = 
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType            = 
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback        = DebugCallback,
        .pUserData              = nullptr
    };
}

///////////////////////////////////////////////////////////

void Instance::PrintLayers()
{
    com::SimpleArray<VkLayerProperties, 20> layers;
    vkEnumerateInstanceLayerProperties(&layers.count, nullptr);
    vkEnumerateInstanceLayerProperties(&layers.count, layers.data);
    for(uint32_t i = 0; i < layers.count; ++i)
        com::Print(layers[i].layerName);
}

///////////////////////////////////////////////////////////

}//ns