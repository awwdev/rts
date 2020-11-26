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

void Context::Create(WindowHandle const& wndHandle)
{
    instance.Create();
    physical.Create(instance);
    device.Create(physical);
    surface.Create(instance, physical, wndHandle);
    swapchain.Create(device, surface);
}

///////////////////////////////////////////////////////////

void Context::Destroy()
{
    swapchain.Destroy();
    surface.Destroy(instance);
    device.Destroy();
    instance.Destroy();
}

///////////////////////////////////////////////////////////

}//ns