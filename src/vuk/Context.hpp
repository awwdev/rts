#pragma once

#include "vuk/Context/Instance.hpp"
#include "vuk/Context/Physical.hpp"
#include "vuk/Context/Device.hpp"
#include "vuk/Context/Surface.hpp"
#include "vuk/Context/Swapchain.hpp"

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Context 
{
    Instance  instance;
    Physical  physical;
    Device    device;
    Surface   surface;
    Swapchain swapchain;

    void Create(WindowHandle const& wndHandle);
    void Destroy();
};

///////////////////////////////////////////////////////////

void Context::Create(WindowHandle const& wndHandle)
{
    instance.Create();
    physical.Create(instance);
    device.Create(physical);
    surface.Create(instance, physical, wndHandle);
    swapchain.Create(device, surface, VK_PRESENT_MODE_FIFO_KHR); //VK_PRESENT_MODE_IMMEDIATE_KHR
    Print_VK_VERSION(physical.physicalProps);
}

///////////////////////////////////////////////////////////

void Context::Destroy()
{
    swapchain.Destroy();
    surface.Destroy(instance);
    device.Destroy();
    instance.Destroy();
}

////////////////////////////////////////////////////////////

}//ns