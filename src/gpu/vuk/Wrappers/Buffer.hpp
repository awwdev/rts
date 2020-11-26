#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include <cstring>

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

inline uint32_t MemoryType(
    const VkPhysicalDeviceMemoryProperties& physicalMemProps,
    const VkMemoryRequirements& memReqs,
    const VkMemoryPropertyFlags neededMemProps) 
{
    for (uint32_t i = 0; i < physicalMemProps.memoryTypeCount; ++i) {
        if (memReqs.memoryTypeBits & (1 << i) &&
            (physicalMemProps.memoryTypes[i].propertyFlags & neededMemProps) == neededMemProps) 
            return i;
    }
    com::PrintError("no suitable memory type found!");
    return {};
}

///////////////////////////////////////////////////////////

struct Buffer
{
    VkBuffer buffer;
    VkDeviceMemory memory;
    void* memPtr;
    size_t allocationSize;

    void Create(VkBufferUsageFlags, size_t, VkMemoryPropertyFlags);
    void Destroy();
    void Store(void*, size_t, size_t);
    void Map();
    void Unmap();
};

///////////////////////////////////////////////////////////

void Buffer::Create(VkBufferUsageFlags usage, size_t pSize, VkMemoryPropertyFlags memProps)
{
    VkBufferCreateInfo bufferInfo 
    {
        .sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext                  = nullptr,
        .flags                  = 0,
        .size                   = pSize,
        .usage                  = usage,
        .sharingMode            = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount  = 0,
        .pQueueFamilyIndices    = nullptr
    };
    VkCheck(vkCreateBuffer(g_devicePtr, &bufferInfo, nullptr, &buffer));

    VkMemoryRequirements memReqs;
    vkGetBufferMemoryRequirements(g_devicePtr, buffer, &memReqs);
    allocationSize = memReqs.size;

    //VkMemoryAllocateInfo allocInfo
    //{
    //    .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    //    .pNext           = nullptr,
    //    .allocationSize  = allocationSize,
    //    .memoryTypeIndex = MemoryType(g_devicePtr, memReqs, memProps)
    //};

    //VkCheck(vkAllocateMemory(g_devicePtr, &allocInfo, nullptr, &memory));
    //VkCheck(vkBindBufferMemory(g_devicePtr, buffer, memory, 0));
    //allocationSize = memReqs.size;
}

///////////////////////////////////////////////////////////

void Buffer::Destroy()
{
    vkDestroyBuffer (g_devicePtr, buffer, GetAlloc());
    vkFreeMemory    (g_devicePtr, memory, GetAlloc()); //will unmap
    *this = {};
}

///////////////////////////////////////////////////////////

void Buffer::Store(void* data, size_t size, size_t offset)
{
    std::memcpy((char*)memPtr + offset, data, size);
}

////////////////////////////////////////////////////////////

void Buffer::Map()
{
    VkCheck(vkMapMemory(g_devicePtr, memory, 0, VK_WHOLE_SIZE, 0, &memPtr));
}

////////////////////////////////////////////////////////////

void Buffer::Unmap()
{
    vkUnmapMemory(g_devicePtr, memory);
}

///////////////////////////////////////////////////////////

}//ns