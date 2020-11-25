#pragma once

#include "vuk/Vulkan.hpp"
#include "com/Types.hpp"
#include "com/Clock.hpp"
#include "vuk/Context/InstanceExt.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

////////////////////////////////////////////////////////////

struct Instance 
{
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    void Create();
    void Destroy();
};

///////////////////////////////////////////////////////////

void Instance::Create()
{
    VkApplicationInfo appInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext                  = nullptr,
        .pApplicationName       = "mini",
        .applicationVersion     = 0,
        .pEngineName            = "mini",
        .engineVersion          = 0,
        .apiVersion             = VK_API_VERSION_1_0,
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

    auto debugInfo = DebugMessengerInfo();

    VkInstanceCreateInfo instInfo 
    {
        .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext                   = &debugInfo, //so instance creation messages are handled
        .flags                   = 0,
        .pApplicationInfo        = &appInfo,
        .enabledLayerCount       = array_extent(layers), 
        .ppEnabledLayerNames     = layers,
        .enabledExtensionCount   = array_extent(extensions),
        .ppEnabledExtensionNames = extensions
    };
    VkCheck(vkCreateInstance(&instInfo, GetAlloc(), &instance));

    ((PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"))
    (instance, &debugInfo, GetAlloc(), &debugMessenger);
}

///////////////////////////////////////////////////////////

void Instance::Destroy()
{
    ((PFN_vkDestroyDebugUtilsMessengerEXT) 
    vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"))(instance, debugMessenger, GetAlloc());
    vkDestroyInstance(instance, GetAlloc());
}

///////////////////////////////////////////////////////////

}//ns