#pragma once

#include "gpu/vuk/Renderer/Commands.hpp"

#include "gpu/vuk/States/StateSprites.hpp"
#include "gpu/vuk/States/StatePost.hpp"
#include "gpu/vuk/States/StateUI.hpp"
#include "gpu/vuk/States/StateWire.hpp"

#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct States
{
    StateSprites sprites;
    StatePost    post;
    StateUI      ui;
    StateWire    wire;

    void Create(Context&, Commands&, res::Resources&, RenderData&);
    void Destroy();
    void Record(Commands&, uint32_t);
    void Update(RenderData&, uint32_t);
};

///////////////////////////////////////////////////////////

void States::Create(Context& context, Commands& commands, res::Resources& resources, RenderData& rd)
{
    sprites.Create(context, commands, resources);
    post.Create(context, commands, resources, sprites);
    ui.Create(context, commands, resources);

    //? record once
    for(idx_t i = 0; i < context.swapchain.Count(); ++i)
    {
        Update(rd, i); //so push constants are updated
        Record(commands, i);   
    }
}

///////////////////////////////////////////////////////////

void States::Destroy()
{
    post.Destroy();
    sprites.Destroy();
    ui.Destroy();
}

///////////////////////////////////////////////////////////

void States::Update(RenderData& rd, u32 imageIndex)
{
    sprites.Update(rd.sprites, imageIndex);
    post.Update(rd.post);
    ui.Update(rd.ui);
}

///////////////////////////////////////////////////////////

void States::Record(Commands& commands, uint32_t imageIndex)
{
    auto cmdBuffer = commands.buffers[imageIndex];
    auto beginInfo = CreateCmdBeginInfo();
    VkCheck(vkBeginCommandBuffer(cmdBuffer, &beginInfo));
    sprites.Record(cmdBuffer, imageIndex);
    post.Record(cmdBuffer, imageIndex);
    ui.Record(cmdBuffer, imageIndex);
    VkCheck(vkEndCommandBuffer(cmdBuffer));
}

///////////////////////////////////////////////////////////

}//ns