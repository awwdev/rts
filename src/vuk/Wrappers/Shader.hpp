#pragma once

#include "vuk/Context.hpp"
#include "com/Types.hpp"
#include "com/Assert.hpp"
#include <fstream>

namespace mini::vuk {

inline VkShaderModule LoadShaderModule(chars_t);
inline VkPipelineShaderStageCreateInfo CreateShaderInfo(VkShaderStageFlagBits, VkShaderModule);

///////////////////////////////////////////////////////////

struct Shader
{
    VkShaderModule moduleVert;
    VkShaderModule moduleFrag;
    VkPipelineShaderStageCreateInfo infoVert;
    VkPipelineShaderStageCreateInfo infoFrag;

    void Create(chars_t, chars_t);
    void Destroy();
};

////////////////////////////////////////////////////////////

void Shader::Create(chars_t pathVert, chars_t pathFrag)
{
    moduleVert = LoadShaderModule(pathVert);
    moduleFrag = LoadShaderModule(pathFrag);
    infoVert = CreateShaderInfo(VK_SHADER_STAGE_VERTEX_BIT, moduleVert);
    infoFrag = CreateShaderInfo(VK_SHADER_STAGE_FRAGMENT_BIT, moduleVert);
}

////////////////////////////////////////////////////////////

void Shader::Destroy()
{
    vkDestroyShaderModule(g_devicePtr, moduleVert, nullptr);    
    vkDestroyShaderModule(g_devicePtr, moduleFrag, nullptr);    
}

////////////////////////////////////////////////////////////

inline VkShaderModule LoadShaderModule(chars_t path)
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
        .codeSize   = size,
        .pCode      = reinterpret_cast<uint32_t const*>(buffer)
    };
    VkCheck(vkCreateShaderModule(g_devicePtr, &moduleInfo, nullptr, &mod));

    delete[] buffer;
    return mod;
}

////////////////////////////////////////////////////////////

inline VkPipelineShaderStageCreateInfo CreateShaderInfo(VkShaderStageFlagBits stage, VkShaderModule mod)
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