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
    
    //union 
    //{
        SwapResource<VkDescriptorBufferInfo> bufferInfos;
        SwapResource<VkDescriptorImageInfo>  imageInfos;
    //};
};

///////////////////////////////////////////////////////////

struct Descriptors
{
    VkDescriptorPool pool;
    SwapResource<VkDescriptorSetLayout> layouts;
    SwapResource<VkDescriptorSet> sets; //!

    void Destroy();

    template<auto UNIFORM_COUNT>
    void Create(UniformInfo (&uniformInfos) [UNIFORM_COUNT])
    {
        //set layout
        VkDescriptorSetLayoutBinding bindings [UNIFORM_COUNT];
        for(uint32_t i = 0; i < UNIFORM_COUNT; ++i) {
            bindings[i] = uniformInfos[i].binding;
        }

        layouts.count = g_contextPtr->swapchain.Count();
        for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
        {
            VkDescriptorSetLayoutCreateInfo descSetLayoutInfo
            {
                .sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                .pNext          = nullptr,
                .flags          = 0,
                .bindingCount   = array_extent(bindings),
                .pBindings      = bindings
            };
            VkCheck(vkCreateDescriptorSetLayout(g_devicePtr, &descSetLayoutInfo, GetVkAlloc(), &layouts[i]));
        }
        
        //pool
        VkDescriptorPoolSize poolSizes [UNIFORM_COUNT];
        for(uint32_t i = 0; i < UNIFORM_COUNT; ++i) {
            poolSizes[i] = {
                .type = bindings[i].descriptorType,
                .descriptorCount = g_contextPtr->swapchain.Count() //!
            };
        }

        VkDescriptorPoolCreateInfo poolInfo
        {
            .sType          = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .pNext          = nullptr,
            .flags          = 0,
            .maxSets        = g_contextPtr->swapchain.Count(),//!
            .poolSizeCount  = array_extent(poolSizes),
            .pPoolSizes     = poolSizes
        };
        VkCheck(vkCreateDescriptorPool(g_devicePtr, &poolInfo, GetVkAlloc(), &pool));

        //allocation
        sets.count = g_contextPtr->swapchain.Count();
        VkDescriptorSetAllocateInfo allocInfo
        {
            .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext              = nullptr,
            .descriptorPool     = pool,
            .descriptorSetCount = g_contextPtr->swapchain.Count(), //!
            .pSetLayouts        = layouts.data
        };
        VkCheck(vkAllocateDescriptorSets(g_devicePtr, &allocInfo, sets.data));

        //write
        VkWriteDescriptorSet writes [UNIFORM_COUNT * 4];
        for(idx_t i = 0; i < g_contextPtr->swapchain.Count(); ++i)
        {
            for(idx_t j = 0; j < UNIFORM_COUNT; ++j)
            {
                writes[i*UNIFORM_COUNT + j] =
                {
                    .sType              = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                    .pNext              = nullptr,
                    .dstSet             = sets.data[i],//!
                    .dstBinding         = uniformInfos[j].binding.binding,
                    .dstArrayElement    = 0,
                    .descriptorCount    = 1,
                    .descriptorType     = uniformInfos[j].binding.descriptorType,
                    .pImageInfo         = uniformInfos[j].type == UniformInfo::Image  ? &uniformInfos[j].imageInfos[i]  : nullptr,
                    .pBufferInfo        = uniformInfos[j].type == UniformInfo::Buffer ? &uniformInfos[j].bufferInfos[i] : nullptr,
                    .pTexelBufferView   = nullptr
                };
            }
        }
        vkUpdateDescriptorSets(g_devicePtr, UNIFORM_COUNT * g_contextPtr->swapchain.Count(), writes, 0, nullptr);   
    }
};

///////////////////////////////////////////////////////////

void Descriptors::Destroy()
{
    FOR_ARRAY(layouts, i)
        vkDestroyDescriptorSetLayout(g_devicePtr, layouts[i], GetVkAlloc());
    vkDestroyDescriptorPool(g_devicePtr, pool, GetVkAlloc());
    sets.count = 0;
}

///////////////////////////////////////////////////////////

}//ns