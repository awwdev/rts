#include <iostream>

#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan.h"

int main()
{
    const VkApplicationInfo appInfo {
        .sType                  = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext                  = nullptr,
        .pApplicationName       = nullptr,
        .applicationVersion     = 0,
        .pEngineName            = nullptr,
        .engineVersion          = 0,
        .apiVersion             = VK_API_VERSION_1_0
    };

    const char* layers[1] {
        "VK_LAYER_KHRONOS_validation"
    };

    const char* extensions[3] {
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    };

    const VkInstanceCreateInfo instInfo {
        .sType                  = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .pApplicationInfo       = &appInfo,
        .enabledLayerCount      = 1, 
        .ppEnabledLayerNames    = layers,
        .enabledExtensionCount  = 3,
        .ppEnabledExtensionNames = extensions
    };
    VkInstance instance;
    vkCreateInstance(&instInfo, nullptr, &instance);

    VkPhysicalDevice physicals [4];
    uint32_t physicalsCount;
    vkEnumeratePhysicalDevices(instance, &physicalsCount, nullptr);
    vkEnumeratePhysicalDevices(instance, &physicalsCount, physicals);

    VkPhysicalDeviceProperties physicalProps;
    vkGetPhysicalDeviceProperties(physicals[0], &physicalProps);

    std::cout << 
        VK_VERSION_MAJOR(physicalProps.apiVersion) <<
        VK_VERSION_MINOR(physicalProps.apiVersion) << 
        VK_VERSION_PATCH(physicalProps.apiVersion);

    std::cout << "Hello";
    system("pause");
}