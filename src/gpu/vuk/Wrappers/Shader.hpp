#pragma once

#include "gpu/vuk/Vulkan.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "mem/Memory.hpp"
#include <fstream>

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

template<auto N>
struct Shader
{
    VkShaderModule modules [N];
    VkPipelineShaderStageCreateInfo stageInfos [N];

    void Create(chars_t, chars_t);
    void Destroy();

    static VkShaderModule LoadShaderModule(chars_t);
    static VkPipelineShaderStageCreateInfo CreateShaderInfo(VkShaderStageFlagBits, VkShaderModule);
};

///////////////////////////////////////////////////////////

using FragVertShader = Shader<2>;

///////////////////////////////////////////////////////////

template<auto N>
void Shader<N>::Create(chars_t pathVert, chars_t pathFrag)
{
    modules[0] = LoadShaderModule(pathVert);
    modules[1] = LoadShaderModule(pathFrag);
    stageInfos[0] = CreateShaderInfo(VK_SHADER_STAGE_VERTEX_BIT, modules[0]);
    stageInfos[1] = CreateShaderInfo(VK_SHADER_STAGE_FRAGMENT_BIT, modules[1]);
}

///////////////////////////////////////////////////////////

template<auto N>
void Shader<N>::Destroy()
{
    vkDestroyShaderModule(g_devicePtr, modules[0], GetVkAlloc());    
    vkDestroyShaderModule(g_devicePtr, modules[1], GetVkAlloc());    
}

///////////////////////////////////////////////////////////

template<auto N>
VkShaderModule Shader<N>::LoadShaderModule(chars_t path)
{
    VkShaderModule mod;

    std::ifstream file(path, std::ios::ate | std::ios::binary);
    com::Assert(file.is_open(), "cannot open shader file");

    struct Arr { char buffer [10'000]; }; //capacity based
    auto ptr = rts::mem::ClaimBlock<Arr>();

    auto size = file.tellg();
    com::Assert((size_t)size < sizeof(Arr::buffer), "shader read exhausted");
    file.seekg(std::ios::beg);
    file.read(ptr->buffer, size);

    VkShaderModuleCreateInfo moduleInfo 
    {
        .sType      = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext      = nullptr,
        .flags      = 0,
        .codeSize   = (uint32_t)size,
        .pCode      = reinterpret_cast<uint32_t const*>(ptr->buffer)
    };
    VkCheck(vkCreateShaderModule(g_devicePtr, &moduleInfo, GetVkAlloc(), &mod));

    return mod;
}

///////////////////////////////////////////////////////////

template<auto N>
VkPipelineShaderStageCreateInfo 
Shader<N>::CreateShaderInfo(VkShaderStageFlagBits stage, VkShaderModule mod)
{
    return {
        .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .pNext  = nullptr,
        .flags  = 0,
        .stage  = stage,
        .module = mod,
        .pName  = "main",
        .pSpecializationInfo = nullptr 
    };
}

///////////////////////////////////////////////////////////

}//ns