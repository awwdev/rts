#pragma once

#include "gpu/vuk/Renderer/Context.hpp"
#include "com/Array.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

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

    void Create();
    void Destroy();
};

///////////////////////////////////////////////////////////

void Descriptors::Create()
{

}

///////////////////////////////////////////////////////////

void Descriptors::Destroy()
{

}

///////////////////////////////////////////////////////////

}//ns