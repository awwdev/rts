#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Device.hpp"
#include "vuk/Context/Surface.hpp"

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Swapchain
{
    VkSwapchainKHR swapchain;
    uint32_t swapImagesCount;
    VkImage* swapImages;
    uint32_t swapImageViewsCount;
    VkImageView* swapImageViews;

    void Create(Device&, Surface&, VkPresentModeKHR);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Swapchain::Create(Device& device, Surface& surface, VkPresentModeKHR presentMode)
{
    constexpr VkFormat format = VK_FORMAT_B8G8R8A8_SRGB;

    VkSwapchainCreateInfoKHR const swapInfo
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

    VkCheck(vkCreateSwapchainKHR(device.device, &swapInfo, nullptr, &swapchain));


    VkCheck(vkGetSwapchainImagesKHR(device.device, swapchain, &swapImagesCount, nullptr));
    swapImages = new VkImage[swapImagesCount];
    VkCheck(vkGetSwapchainImagesKHR(device.device, swapchain, &swapImagesCount, swapImages));

    swapImageViewsCount = swapImagesCount;
    swapImageViews = new VkImageView[swapImageViewsCount];
    //com::Print("swapImagesCount", swapImagesCount);

    for (u32 i = 0; i < swapImagesCount; ++i) 
    {
        VkImageViewCreateInfo const viewInfo 
        {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext      = nullptr,
            .flags      = 0,
            .image      = swapImages[i],
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
        VkCheck(vkCreateImageView(device.device, &viewInfo, nullptr, &swapImageViews[i]));
    }
}

///////////////////////////////////////////////////////////

void Swapchain::Destroy()
{
    vkDestroySwapchainKHR(g_devicePtr, swapchain, nullptr);
    for(uint32_t i = 0; i < swapImageViewsCount; ++i)
        vkDestroyImageView(g_devicePtr, swapImageViews[i], nullptr);
    delete[] swapImageViews;
    delete[] swapImages;
}

///////////////////////////////////////////////////////////

}//ns