#pragma once

#include "gpu/vuk/Commands/Commands.hpp"

#include "gpu/vuk/States/StateGeneral.hpp"
#include "gpu/vuk/States/StatePost.hpp"
#include "gpu/vuk/States/StateUI.hpp"

#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct States
{
    StateGeneral general;
    StatePost    post;
    StateUI      ui;

    void Create(Context&, Commands&, res::Resources&, RenderData&);
    void Destroy();
    void Record(Commands&, uint32_t);
    void Update(RenderData&, uint32_t);
};

///////////////////////////////////////////////////////////

void States::Create(Context& context, Commands& commands, res::Resources& resources, RenderData& rd)
{
    general.Create(context, commands, resources);
    post.Create(context, commands, resources, general);
    ui.Create(context, commands, resources);

    //record once
    for(idx_t i = 0; i < context.swapchain.Count(); ++i)
    {
        Update(rd, i);
        Record(commands, i);   
    }
}

///////////////////////////////////////////////////////////

void States::Destroy()
{
    post.Destroy();
    general.Destroy();
    ui.Destroy();
}

///////////////////////////////////////////////////////////

void States::Update(RenderData& rd, u32 swapIdx)
{
    general.Update(rd, swapIdx);
    post.Update(rd, swapIdx);
    ui.Update(rd, swapIdx);
}

///////////////////////////////////////////////////////////

void States::Record(Commands& commands, uint32_t swapidx)
{
    auto cmdBuffer = commands.buffers[swapidx];
    auto beginInfo = CreateCmdBeginInfo();
    VkCheck(vkBeginCommandBuffer(cmdBuffer, &beginInfo));
    general.Record(cmdBuffer, swapidx);
    post.Record(cmdBuffer, swapidx);
    ui.Record(cmdBuffer, swapidx);
    VkCheck(vkEndCommandBuffer(cmdBuffer));
}

///////////////////////////////////////////////////////////

}//ns