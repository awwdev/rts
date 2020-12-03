#pragma once

#include "gpu/vuk/Renderer/Context.hpp"
#include "com/Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct UniformInfo
{
    enum Type { Buffer, Image } type;
    VkDescriptorSetLayoutBinding binding;
    union 
    {
        VkDescriptorBufferInfo bufferInfo;
        VkDescriptorImageInfo  imageInfo;
    };
};

///////////////////////////////////////////////////////////

struct Descriptors
{
    VkDescriptorPool pool;
    VkDescriptorSetLayout layout;
    com::Array<VkDescriptorSet, 10> sets;

    void Destroy();

    template<auto UNIFORM_COUNT>
    void Create(UniformInfo (&uniformInfos) [UNIFORM_COUNT])
    {
        //set layout
        VkDescriptorSetLayoutBinding bindings [UNIFORM_COUNT];
        for(uint32_t i = 0; i < UNIFORM_COUNT; ++i) {
            bindings[i] = uniformInfos[i].binding;
        }

        VkDescriptorSetLayoutCreateInfo descSetLayoutInfo
        {
            .sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext          = nullptr,
            .flags          = 0,
            .bindingCount   = array_extent(bindings),
            .pBindings      = bindings
        };
        VkCheck(vkCreateDescriptorSetLayout(g_devicePtr, &descSetLayoutInfo, GetVkAlloc(), &layout));

        //pool
        VkDescriptorPoolSize poolSizes [UNIFORM_COUNT];
        for(uint32_t i = 0; i < UNIFORM_COUNT; ++i) {
            poolSizes[i] = {
                .type = bindings[i].descriptorType,
                .descriptorCount = 1
            };
        }

        VkDescriptorPoolCreateInfo poolInfo
        {
            .sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .pNext          = nullptr,
            .flags          = 0,
            .maxSets        = g_contextPtr->swapchain.images.count,
            .poolSizeCount  = array_extent(poolSizes),
            .pPoolSizes     = poolSizes
        };
        VkCheck(vkCreateDescriptorPool(g_devicePtr, &poolInfo, GetVkAlloc(), &pool));

        //allocation
        sets.count = 1;
        VkDescriptorSetAllocateInfo allocInfo
        {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext              = nullptr,
            .descriptorPool     = pool,
            .descriptorSetCount = sets.count,
            .pSetLayouts        = &layout
        };
        VkCheck(vkAllocateDescriptorSets(g_devicePtr, &allocInfo, sets.data));

        //write
        VkWriteDescriptorSet writes [UNIFORM_COUNT];
        FOR_C_ARRAY(writes, i)
        {
            writes[i] = VkWriteDescriptorSet {
                .sType              = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext              = nullptr,
                .dstSet             = sets.data[0],
                .dstBinding         = uniformInfos[i].binding.binding,
                .dstArrayElement    = 0,
                .descriptorCount    = 1,
                .descriptorType     = uniformInfos[i].binding.descriptorType,
                .pImageInfo         = uniformInfos[i].type == UniformInfo::Image  ? &uniformInfos[i].imageInfo  : nullptr,
                .pBufferInfo        = uniformInfos[i].type == UniformInfo::Buffer ? &uniformInfos[i].bufferInfo : nullptr,
                .pTexelBufferView   = nullptr
            };
        }
        vkUpdateDescriptorSets(g_devicePtr, array_extent(writes), writes, 0, nullptr);   
    }
};

///////////////////////////////////////////////////////////

void Descriptors::Destroy()
{
    vkDestroyDescriptorSetLayout(g_devicePtr, layout, GetVkAlloc());
    vkDestroyDescriptorPool(g_devicePtr, pool, GetVkAlloc());
    sets.count = 0;
}

///////////////////////////////////////////////////////////

}//ns