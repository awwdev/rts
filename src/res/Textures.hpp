#pragma once

#include <filesystem>
#include <fstream>
#include "com/Assert.hpp"
#include "com/POD_Array.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::res {

///////////////////////////////////////////////////////////

struct Texture
{
    static constexpr auto SIZE = 32*32*4;
    char buffer [SIZE];
};

///////////////////////////////////////////////////////////

struct Textures
{
    com::POD_Array<Texture, 10> sprites;
    void Load();
};

///////////////////////////////////////////////////////////

void Textures::Load()
{
    for(auto& it : std::filesystem::directory_iterator("res/Textures/sprites/")) 
    {
        com::Print("loading", it.path());
        auto& texture = sprites.Append();
        std::ifstream file { it.path(), std::ios::binary };
        com::Assert(file.is_open(), "cannot open file");
        file.read(texture.buffer, texture.SIZE);
    }    
}

///////////////////////////////////////////////////////////

}//ns