#pragma once

#include "vuk/Vulkan.hpp"
#include "vuk/Context/Surface.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Swapchain
{
    VkSwapchainKHR swapchain;
    uint32_t swapImagesCount;
    VkImage* swapImages;
    uint32_t swapImageViewsCount;
    VkImageView* swapImageViews;
};

///////////////////////////////////////////////////////////

static void CreateSwapchain(
VkDevice device, 
Swapchain& swapchain,
Surface& surface, 
VkFormat format,
VkColorSpaceKHR colorSpace,
VkPresentModeKHR presentMode)
{

    VkSwapchainCreateInfoKHR const swapInfo
        {
        .sType                  = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext                  = nullptr,
        .flags                  = 0,
        .surface                = surface.surface,
        .minImageCount          = surface.capabilities.minImageCount + 1,
        .imageFormat            = format,
        .imageColorSpace        = colorSpace,
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

    VkCheck(vkCreateSwapchainKHR(device, &swapInfo, nullptr, &swapchain.swapchain));


    VkCheck(vkGetSwapchainImagesKHR(device, swapchain.swapchain, &swapchain.swapImagesCount, nullptr));
    swapchain.swapImages = new VkImage[swapchain.swapImagesCount];
    VkCheck(vkGetSwapchainImagesKHR(device, swapchain.swapchain, &swapchain.swapImagesCount, swapchain.swapImages));

    swapchain.swapImageViewsCount = swapchain.swapImagesCount;
    swapchain.swapImageViews = new VkImageView[swapchain.swapImageViewsCount];
    com::Print("swapImagesCount", swapchain.swapImagesCount);

    for (u32 i = 0; i < swapchain.swapImagesCount; ++i) 
    {
        VkImageViewCreateInfo const viewInfo 
        {
            .sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext      = nullptr,
            .flags      = 0,
            .image      = swapchain.swapImages[i],
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
        VkCheck(vkCreateImageView(device, &viewInfo, nullptr, &swapchain.swapImageViews[i]));
    }
}

///////////////////////////////////////////////////////////

static void DestroySwapchain(VkDevice device, Swapchain swapchain)
{
    vkDestroySwapchainKHR(device, swapchain.swapchain, nullptr);
    for(uint32_t i = 0; i < swapchain.swapImageViewsCount; ++i)
        vkDestroyImageView(device, swapchain.swapImageViews[i], nullptr);
    delete[] swapchain.swapImageViews;
    delete[] swapchain.swapImages;
}

///////////////////////////////////////////////////////////

}//ns