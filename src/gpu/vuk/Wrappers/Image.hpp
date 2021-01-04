#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "gpu/vuk/Renderer/CommandsExt.hpp"
#include "gpu/vuk/Wrappers/Buffer.hpp"
#include "mem/Memory.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

constexpr VkComponentMapping IMAGE_COMPONENT_MAPPING_DEFAULT = 
{ 
    .r = VK_COMPONENT_SWIZZLE_R,
    .g = VK_COMPONENT_SWIZZLE_G,
    .b = VK_COMPONENT_SWIZZLE_B,
    .a = VK_COMPONENT_SWIZZLE_A
};

///////////////////////////////////////////////////////////

struct Image
{
    VkImage image = nullptr;
    VkDeviceMemory memory = nullptr;
    VkImageView view = nullptr;
    VkImageLayout layout = VK_IMAGE_LAYOUT_MAX_ENUM;
    VkImageAspectFlagBits aspect = VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
    u32 layerCount = 0;
    u32 width = 0;
    u32 height = 0;

    void Create(
        VkCommandPool, 
        VkFormat, 
        VkImageUsageFlags, 
        VkImageViewType,
        u32, u32, u32,
        bool transitionForStoring = false
    );

    void Destroy();
    void Store(VkCommandPool, void const*, u32, u32);
    void Bake(VkCommandPool);

    void Transition(
        VkCommandPool, VkImageLayout,
        VkAccessFlags, VkAccessFlags, 
        VkPipelineStageFlags, VkPipelineStageFlags
    );
};

///////////////////////////////////////////////////////////

void Image::Create(
VkCommandPool cmdPool, 
VkFormat format, 
VkImageUsageFlags usage, 
VkImageViewType viewType,
u32 pWidth, u32 pHeight, u32 pLayerCount,
bool transitionForStoring)
{
    layout = VK_IMAGE_LAYOUT_UNDEFINED;
    aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    layerCount = pLayerCount;
    width = pWidth;
    height = pHeight;

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
    VkCheck(vkCreateImage(g_devicePtr, &imageInfo, GetVkAlloc(), &image));

    AllocateMemory(image, memory, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    VkImageViewCreateInfo viewInfo 
    {
        .sType              = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .pNext              = nullptr,
        .flags              = 0, 
        .image              = image, 
        .viewType           = viewType, 
        .format             = format,
        .components         = IMAGE_COMPONENT_MAPPING_DEFAULT,
        .subresourceRange   = 
        {
            .aspectMask     = aspect,
            .baseMipLevel   = 0,
            .levelCount     = 1,
            .baseArrayLayer = 0,
            .layerCount     = layerCount
        }
    };
    VkCheck(vkCreateImageView(g_devicePtr, &viewInfo, GetVkAlloc(), &view));

    if (transitionForStoring)
    {
        Transition(
        cmdPool, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 
        0, VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    }
}

///////////////////////////////////////////////////////////

void Image::Destroy()
{
    vkDestroyImage      (g_devicePtr, image, GetVkAlloc());
    vkFreeMemory        (g_devicePtr, memory, GetVkAlloc());
    vkDestroyImageView  (g_devicePtr, view, GetVkAlloc());       
    *this = {};
}

///////////////////////////////////////////////////////////

void Image::Store(VkCommandPool cmdPool, void const* data, u32 singleTextureSize, u32 count)
{
    auto totalSize = count * singleTextureSize;

    Buffer tmpBuffer;
    tmpBuffer.Create(
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT, totalSize, 
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    );
    tmpBuffer.Map();
    tmpBuffer.Store(data, totalSize);

    struct Arr { VkBufferImageCopy data [250]; };
    auto ptr = mem::ClaimBlock<Arr>();
    auto& imageCopyInfos = ptr->data;

    for(u32 layerIdx = 0; layerIdx < layerCount; ++layerIdx)
    {
        imageCopyInfos[layerIdx] = 
        {
            .bufferOffset       = layerIdx * singleTextureSize,
            .bufferRowLength    = 0,
            .bufferImageHeight  = 0,
            .imageSubresource   = 
            {
                .aspectMask     = aspect,
                .mipLevel       = 0,
                .baseArrayLayer = layerIdx,
                .layerCount     = 1
            },
            .imageOffset        = { 0, 0, 0 },
            .imageExtent        = { width, height, 1 }
        };
    }

    //send to queue
    auto cmdBuffer = BeginCommands_OneTime(cmdPool);
    vkCmdCopyBufferToImage(
        cmdBuffer, 
        tmpBuffer.buffer, image, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 
        layerCount, imageCopyInfos
    );
    EndCommands_OneTime(cmdBuffer, cmdPool);

    tmpBuffer.Destroy();
}

///////////////////////////////////////////////////////////

void Image::Bake(VkCommandPool cmdPool)
{
    Transition(
        cmdPool, 
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, 
        VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT,
        VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
    );
}

///////////////////////////////////////////////////////////

void Image::Transition(
VkCommandPool cmdPool,
VkImageLayout newLayout,
VkAccessFlags srcAccessMask,
VkAccessFlags dstAccessMask, 
VkPipelineStageFlags srcStageMask,
VkPipelineStageFlags dstStageMask)
{
    auto cmdBuffer = BeginCommands_OneTime(cmdPool);

    VkImageMemoryBarrier barrier
    {
        .sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        .pNext               = nullptr,
        .srcAccessMask       = srcAccessMask,
        .dstAccessMask       = dstAccessMask,
        .oldLayout           = layout,
        .newLayout           = newLayout,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image               = image,
        .subresourceRange    = 
        {
            .aspectMask      = aspect,
            .baseMipLevel    = 0,
            .levelCount      = 1,
            .baseArrayLayer  = 0,
            .layerCount      = layerCount
        }
    };

    layout = newLayout;

    vkCmdPipelineBarrier(
        cmdBuffer,
        srcStageMask, 
        dstStageMask,
        0,
        0, nullptr,
        0, nullptr,
        1, &barrier
    );

    EndCommands_OneTime(cmdBuffer, cmdPool);
}

///////////////////////////////////////////////////////////

}//ns