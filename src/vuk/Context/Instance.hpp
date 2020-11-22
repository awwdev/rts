#pragma once

#include "vuk/Vulkan.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

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

inline void Print_VkLayerProperties()
{
    uint32_t count;
    VkLayerProperties* layerProps;
    vkEnumerateInstanceLayerProperties(&count, nullptr);
    layerProps = new VkLayerProperties [count];
    vkEnumerateInstanceLayerProperties(&count, layerProps);
    for(uint32_t i = 0; i < count; ++i)
        com::Print(layerProps[i].layerName);
    delete[] layerProps;
}

////////////////////////////////////////////////////////////

inline auto Create_VkDebugUtilsMessengerCreateInfoEXT()
{
    return VkDebugUtilsMessengerCreateInfoEXT
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

static void CreateInstance(
VkInstance& instance, 
VkDebugUtilsMessengerEXT& debugMessenger,
uint32_t apiVersion = VK_API_VERSION_1_0,
chars_t  appName = "mini", 
uint32_t appVersion = 0,
chars_t  engineName = "mini",
uint32_t engineVersion = 0)
{
    VkApplicationInfo const appInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext                  = nullptr,
        .pApplicationName       = appName,
        .applicationVersion     = appVersion,
        .pEngineName            = engineName,
        .engineVersion          = engineVersion,
        .apiVersion             = apiVersion,
    };

    chars_t layers[] 
    {
        #ifdef _WIN32
        "VK_LAYER_KHRONOS_validation"
        #endif
        #ifdef __linux__
        "VK_LAYER_LUNARG_standard_validation"
        #endif
    };
    
    chars_t extensions[] 
    {
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        VK_KHR_SURFACE_EXTENSION_NAME,
        
        #ifdef _WIN32
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
        #endif
        #ifdef __linux__
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
        #endif
    };

    auto const debugCreateInfo = Create_VkDebugUtilsMessengerCreateInfoEXT();

    VkInstanceCreateInfo const instInfo 
    {
        .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext                   = &debugCreateInfo, //so instance creation messages are handled
        .flags                   = 0,
        .pApplicationInfo        = &appInfo,
        .enabledLayerCount       = array_extent(layers), 
        .ppEnabledLayerNames     = layers,
        .enabledExtensionCount   = array_extent(extensions),
        .ppEnabledExtensionNames = extensions
    };

    VkCheck(vkCreateInstance(&instInfo, nullptr, &instance));

    ((PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"))
    (instance, &debugCreateInfo, nullptr, &debugMessenger);
}

///////////////////////////////////////////////////////////

static void DestroyInstance(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger)
{
    ((PFN_vkDestroyDebugUtilsMessengerEXT) 
    vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))(instance, debugMessenger, nullptr);
    vkDestroyInstance(instance, nullptr);
}

///////////////////////////////////////////////////////////

}//ns