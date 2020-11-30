#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Wrappers/ImageExt.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct Image
{
    VkImage image;
    VkDeviceMemory memory;
    VkImageView view;
    VkImageLayout layout;

    void Create(VkFormat, VkImageUsageFlags, u32, u32, u32);
    void Destroy();
    void Bake();
    void Store(VkCommandPool, void const*, u32, u32);
};

///////////////////////////////////////////////////////////

void Image::Create(
VkFormat format, VkImageUsageFlags usage, u32 width, u32 height, u32 layerCount)
{
    layout = VK_IMAGE_LAYOUT_UNDEFINED;
    VkImageCreateInfo imageInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .imageType              = VK_IMAGE_TYPE_2D,
        .format                 = format,
        .extent                 = VkExtent3D { width, height, 1 },
        .mipLevels              = 1,
        .arrayLayers            = layerCount,
        .samples                = VK_SAMPLE_COUNT_1_BIT,
        .tiling                 = VK_IMAGE_TILING_OPTIMAL,
        .usage                  = usage,
        .sharingMode            = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount  = 0,
        .pQueueFamilyIndices    = 0,
        .initialLayout          = layout
    };
    VkCheck(vkCreateImage(g_devicePtr, &imageInfo, GetAlloc(), &image));

    AllocateMemory(image, memory, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    VkImageViewCreateInfo viewInfo 
    {
        .sType              = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = 0, 
        .image              = image, 
        .viewType           = VK_IMAGE_VIEW_TYPE_2D_ARRAY, 
        .format             = format,
        .components         = IMAGE_COMPONENT_MAPPING_DEFAULT,
        .subresourceRange   = 
        {
            .aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel   = 0,
            .levelCount     = 1,
            .baseArrayLayer = 0,
            .layerCount     = layerCount
        }
    };
    VkCheck(vkCreateImageView(g_devicePtr, &viewInfo, GetAlloc(), &view));
}

///////////////////////////////////////////////////////////

void Image::Destroy()
{
    vkDestroyImage      (g_devicePtr, image, GetAlloc());
    vkFreeMemory        (g_devicePtr, memory, GetAlloc());
    vkDestroyImageView  (g_devicePtr, view, GetAlloc());       
    layout = VK_IMAGE_LAYOUT_UNDEFINED;
}

///////////////////////////////////////////////////////////

void Image::Store(VkCommandPool cmdPool, void const* data, const uint32_t size, const uint32_t singleTextureSize)
{

}

///////////////////////////////////////////////////////////

void Image::Bake()
{

}

///////////////////////////////////////////////////////////

}//ns