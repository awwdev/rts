#pragma once

#include "vuk/Context/Instance.hpp"
#include "vuk/Context/InstanceExt.hpp"
#include "vuk/Context/Physical.hpp"
#include "vuk/Context/PhysicalExt.hpp"
#include "vuk/Context/Device.hpp"
#include "vuk/Context/Surface.hpp"
#include "vuk/Context/SurfaceExt.hpp"
#include "vuk/Context/Swapchain.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Context {

///////////////////////////////////////////////////////////

Instance  instance;
Physical  physical;
Device    device;
Surface   surface;
Swapchain swapchain;

///////////////////////////////////////////////////////////

void Create(WindowHandle const& wndHandle)
{
    instance.Create(VK_API_VERSION_1_0);
    physical.Create(instance);
    device.Create(physical);
    surface.Create(instance, physical, wndHandle);
    swapchain.Create(device, surface, VK_PRESENT_MODE_FIFO_KHR); //VK_PRESENT_MODE_IMMEDIATE_KHR

    Print_VK_VERSION(physical.physicalProps);
    //Print_VkLayerProperties();
    //Print_VkPhysicalDeviceFeatures(physical.physical);
    //Print_VkPhysicalDeviceMemoryProperties(physical.memoryProps);
    //Print_VkPhysicalDeviceProperties(physical.physicalProps);
}

///////////////////////////////////////////////////////////

void Destroy()
{
    swapchain.Destroy();
    surface.Destroy(instance);
    device.Destroy();
    instance.Destroy();
}

///////////////////////////////////////////////////////////

};

///////////////////////////////////////////////////////////

}//ns