#pragma once

#include <filesystem>
#include <fstream>
#include "com/Assert.hpp"
#include "com/Array.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::res {

///////////////////////////////////////////////////////////

struct Texture
{
    static constexpr auto SIZE = 32*32*4;
    char buffer [SIZE];
};

///////////////////////////////////////////////////////////

struct Textures
{
    com::Array<Texture, 10> textureArray;
    void Load();
};

///////////////////////////////////////////////////////////

void Textures::Load()
{
    for(auto& it : std::filesystem::directory_iterator("res/Textures/rgba/")) 
    {
        com::Print("loading", it.path());
        auto& texture = textureArray.Append();
        std::ifstream file { it.path(), std::ios::binary };
        com::Assert(file.is_open(), "cannot open file");
        file.read(texture.buffer, texture.SIZE);
    }    
}

///////////////////////////////////////////////////////////

}//ns