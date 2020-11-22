#pragma once

#include "vuk/Vulkan.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

static void CreateSwapchain(
VkDevice device, 
VkSurfaceKHR surface, 
VkSwapchainKHR& swapchain, 
VkSurfaceCapabilitiesKHR& surfaceCapabilities, 
VkImage*& swapImages,
uint32_t& swapImagesCount,
VkImageView*& swapImageViews,
uint32_t& swapImageViewsCount,
VkFormat format,
VkColorSpaceKHR colorSpace,
VkPresentModeKHR presentMode)
{

    VkSwapchainCreateInfoKHR const swapInfo
        {
        .sType                  = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext                  = nullptr,
        .flags                  = 0,
        .surface                = surface,
        .minImageCount          = surfaceCapabilities.minImageCount + 1,
        .imageFormat            = format,
        .imageColorSpace        = colorSpace,
        .imageExtent            = surfaceCapabilities.currentExtent,
        .imageArrayLayers       = 1,
        .imageUsage             = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode       = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount  = 0,
        .pQueueFamilyIndices    = nullptr,
        .preTransform           = surfaceCapabilities.currentTransform,
        .compositeAlpha         = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode            = presentMode,
        .clipped                = VK_FALSE,
        .oldSwapchain           = nullptr
    };

    VkCheck(vkCreateSwapchainKHR(device, &swapInfo, nullptr, &swapchain));


    VkCheck(vkGetSwapchainImagesKHR(device, swapchain, &swapImagesCount, nullptr));
    swapImages = new VkImage[swapImagesCount];
    VkCheck(vkGetSwapchainImagesKHR(device, swapchain, &swapImagesCount, swapImages));

    swapImageViewsCount = swapImagesCount;
    swapImageViews = new VkImageView[swapImageViewsCount];
    com::Print("swapImagesCount", swapImagesCount);

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
        VkCheck(vkCreateImageView(device, &viewInfo, nullptr, &swapImageViews[i]));
    }
}

///////////////////////////////////////////////////////////

static void DestroySwapchain(VkDevice device, VkSwapchainKHR swapchain, VkImageView* swapImageViews, uint32_t swapImageViewsCount, VkImage* swapImages)
{
    vkDestroySwapchainKHR(device, swapchain, nullptr);
    for(uint32_t i = 0; i < swapImageViewsCount; ++i)
        vkDestroyImageView(device, swapImageViews[i], nullptr);
    delete[] swapImageViews;
    delete[] swapImages;
}

///////////////////////////////////////////////////////////

}//ns