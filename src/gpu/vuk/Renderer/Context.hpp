#pragma once

#include "gpu/vuk/Context/Instance.hpp"
#include "gpu/vuk/Context/Physical.hpp"
#include "gpu/vuk/Context/Device.hpp"
#include "gpu/vuk/Context/Surface.hpp"
#include "gpu/vuk/Context/Swapchain.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct Context 
{
    Instance  instance;
    Physical  physical;
    Device    device;
    Surface   surface;
    Swapchain swapchain;

    void Create(WindowHandle const&);
    void Destroy();
};

///////////////////////////////////////////////////////////

inline Context* g_contextPtr; 
inline VkDevice g_devicePtr;

///////////////////////////////////////////////////////////

void Context::Create(WindowHandle const& wndHandle)
{
    instance.Create();
    physical.Create(instance);
    device.Create(physical);
    surface.Create(instance, physical, wndHandle);
    swapchain.Create(device, surface);

    g_contextPtr = this;
    g_devicePtr = device.device;
}

///////////////////////////////////////////////////////////

void Context::Destroy()
{
    swapchain.Destroy(device.device);
    surface.Destroy(instance.instance);
    device.Destroy();
    instance.Destroy();

    g_contextPtr = nullptr;
    g_devicePtr  = nullptr;
}

///////////////////////////////////////////////////////////

}//ns