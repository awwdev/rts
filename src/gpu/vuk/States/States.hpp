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

void States::Update(RenderData& rd, u32 imageIndex)
{
    general.Update(rd, imageIndex);
    post.Update(rd, imageIndex);
    ui.Update(rd, imageIndex);
}

///////////////////////////////////////////////////////////

void States::Record(Commands& commands, uint32_t imageIndex)
{
    auto cmdBuffer = commands.buffers[imageIndex];
    auto beginInfo = CreateCmdBeginInfo();
    VkCheck(vkBeginCommandBuffer(cmdBuffer, &beginInfo));
    general.Record(cmdBuffer, imageIndex);
    post.Record(cmdBuffer, imageIndex);
    ui.Record(cmdBuffer, imageIndex);
    VkCheck(vkEndCommandBuffer(cmdBuffer));
}

///////////////////////////////////////////////////////////

}//ns