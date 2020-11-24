#pragma once

#include "vuk/Vulkan.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include <fstream>

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Shader
{
    VkShaderModule modules [2];
    VkPipelineShaderStageCreateInfo stageInfos [2];

    void Create(chars_t, chars_t);
    void Destroy();

    static VkShaderModule LoadShaderModule(chars_t);
    static VkPipelineShaderStageCreateInfo CreateShaderInfo(VkShaderStageFlagBits, VkShaderModule);
};

////////////////////////////////////////////////////////////

void Shader::Create(chars_t pathVert, chars_t pathFrag)
{
    modules[0] = LoadShaderModule(pathVert);
    modules[1] = LoadShaderModule(pathFrag);
    stageInfos[0] = CreateShaderInfo(VK_SHADER_STAGE_VERTEX_BIT, modules[0]);
    stageInfos[1] = CreateShaderInfo(VK_SHADER_STAGE_FRAGMENT_BIT, modules[1]);
}

////////////////////////////////////////////////////////////

void Shader::Destroy()
{
    vkDestroyShaderModule(g_devicePtr, modules[0], nullptr);    
    vkDestroyShaderModule(g_devicePtr, modules[1], nullptr);    
}

////////////////////////////////////////////////////////////

VkShaderModule Shader::LoadShaderModule(chars_t path)
{
    VkShaderModule mod;

    std::ifstream file(path, std::ios::ate | std::ios::binary);
    com::Assert(file.is_open(), "cannot open shader file");

    auto size = file.tellg();
    char* buffer = new char[size];
    file.seekg(std::ios::beg);
    file.read(buffer, size);

    VkShaderModuleCreateInfo moduleInfo 
    {
        .sType      = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext      = nullptr,
        .flags      = 0,
        .codeSize   = (uint32_t)size,
        .pCode      = reinterpret_cast<uint32_t const*>(buffer)
    };
    VkCheck(vkCreateShaderModule(g_devicePtr, &moduleInfo, nullptr, &mod));

    delete[] buffer;
    return mod;
}

////////////////////////////////////////////////////////////

VkPipelineShaderStageCreateInfo Shader::CreateShaderInfo(VkShaderStageFlagBits stage, VkShaderModule mod)
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

////////////////////////////////////////////////////////////

}//ns