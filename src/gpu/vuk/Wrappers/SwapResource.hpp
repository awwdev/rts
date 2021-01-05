#pragma once

#include "gpu/vuk/Context/Context.hpp"
#include "com/Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

template<typename T>
using SwapResource = com::Array<T, 4>;

///////////////////////////////////////////////////////////

#define IF(obj) if constexpr(std::is_same_v<T, obj>) 

///////////////////////////////////////////////////////////

template<typename T>
void DestroySwapResource(SwapResource<T>& swapResource)
{
    auto destroyFn = [](auto& element)
    {
        IF (VkFramebuffer)         
            vkDestroyFramebuffer(g_devicePtr, element, GetVkAlloc());  
        IF (VkImageView)           
            vkDestroyImageView(g_devicePtr, element, GetVkAlloc());  
        IF (VkSemaphore)           
            vkDestroySemaphore(g_devicePtr, element, GetVkAlloc());  
        IF (VkFence)               
            vkDestroyFence(g_devicePtr, element, GetVkAlloc()); 
        IF (VkDescriptorSetLayout) 
            vkDestroyDescriptorSetLayout(g_devicePtr, element, GetVkAlloc()); 

        if constexpr (requires { typename std::decay_t<decltype(element)>::BUFFER_TYPEID; })
            element.Destroy();
    };

    FOR_ARRAY(swapResource, i)
    {
        destroyFn(swapResource[i]);
        swapResource[i] = {};
    }  
    swapResource.count = 0;    
}

///////////////////////////////////////////////////////////

#undef IF

///////////////////////////////////////////////////////////

}//ns