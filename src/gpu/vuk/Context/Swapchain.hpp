#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Context/Device.hpp"
#include "gpu/vuk/Context/Surface.hpp"
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct Swapchain
{
    VkSwapchainKHR swapchain;
    com::POD_Array<VkImage, 4> images;
    com::POD_Array<VkImageView, 4> views;
    uint32_t width;
    uint32_t height;
    VkFormat format = VK_FORMAT_B8G8R8A8_UNORM;//VK_FORMAT_B8G8R8A8_SRGB;//VK_FORMAT_B8G8R8A8_UNORM

    //VkPresentModeKHR presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

    void Create(Device&, Surface&);
    void Destroy(VkDevice);
};

///////////////////////////////////////////////////////////

void Swapchain::Create(Device& device, Surface& surface)
{
    width  = surface.capabilities.currentExtent.width;
    height = surface.capabilities.currentExtent.height;

    VkSwapchainCreateInfoKHR swapInfo
    {
        .sType                  = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext                  = nullptr,
        .flags                  = 0,
        .surface                = surface.surface,
        .minImageCount          = surface.capabilities.minImageCount + 1,
        .imageFormat            = format,
        .imageColorSpace        = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
        .imageExtent            = surface.capabilities.currentExtent,
        .imageArrayLayers       = 1,
        .imageUsage             = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode       = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount  = 0,
        .pQueueFamilyIndices    = nullptr,
        .preTransform           = surface.capabilities.currentTransform,
        .compositeAlpha         = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode            = presentMode,
        .clipped                = VK_FALSE,
        .oldSwapchain           = nullptr
    };

    VkCheck(vkCreateSwapchainKHR(device.device, &swapInfo, GetVkAlloc(), &swapchain));


    VkCheck(vkGetSwapchainImagesKHR(device.device, swapchain, &images.count, nullptr));
    VkCheck(vkGetSwapchainImagesKHR(device.device, swapchain, &images.count, images.data));
    views.count = images.count;
    //com::Print("swapImagesCount", swapImagesCount);

    for (u32 i = 0; i < images.count; ++i) 
    {
        VkImageViewCreateInfo const viewInfo 
        {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext      = nullptr,
            .flags      = 0,
            .image      = images[i],
            .viewType   = VK_IMAGE_VIEW_TYPE_2D,
            .format     = format,
            .components = {
                .r = VK_COMPONENT_SWIZZLE_R,
                .g = VK_COMPONENT_SWIZZLE_G,
                .b = VK_COMPONENT_SWIZZLE_B,
                .a = VK_COMPONENT_SWIZZLE_A
            },
            .subresourceRange = {
                .aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel   = 0,
                .levelCount     = 1,
                .baseArrayLayer = 0,
                .layerCount     = 1
            }
        };
        VkCheck(vkCreateImageView(device.device, &viewInfo, GetVkAlloc(), &views[i]));
    }
}

///////////////////////////////////////////////////////////

void Swapchain::Destroy(VkDevice device)
{
    vkDestroySwapchainKHR(device, swapchain, GetVkAlloc());
    FOR_ARRAY(views, i)
    {
        vkDestroyImageView(device, views[i], GetVkAlloc());
        views[i] = nullptr;
    }
    views.count = 0;
    FOR_ARRAY(images, i)
    {
        images[i] = nullptr; //swapchain will destroy images
    }
    images.count = 0;
}

///////////////////////////////////////////////////////////

}//ns