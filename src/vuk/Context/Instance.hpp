#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/InstanceExt.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

////////////////////////////////////////////////////////////

struct Instance {

///////////////////////////////////////////////////////////

VkInstance instance;
VkDebugUtilsMessengerEXT debugMessenger;

///////////////////////////////////////////////////////////

void Create(
uint32_t apiVersion     = VK_API_VERSION_1_0,
chars_t  appName        = "mini", 
uint32_t appVersion     = 0,
chars_t  engineName     = "mini",
uint32_t engineVersion  = 0)
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

void Destroy()
{
    ((PFN_vkDestroyDebugUtilsMessengerEXT) 
    vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))(instance, debugMessenger, nullptr);
    vkDestroyInstance(instance, nullptr);
}

///////////////////////////////////////////////////////////

};

///////////////////////////////////////////////////////////

}//ns