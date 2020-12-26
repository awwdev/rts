#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

#include "com/Assert.hpp"
#include "com/POD_Array.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::res {

///////////////////////////////////////////////////////////

template<auto WIDTH_T, auto HEIGHT_T, auto CHANNELS>
struct Texture
{
    static constexpr auto WIDTH  = WIDTH_T;
    static constexpr auto HEIGHT = HEIGHT_T;
    static constexpr auto SIZE = WIDTH * HEIGHT * CHANNELS;
    char buffer [SIZE];
};

using RGBA_32x32 = Texture<32, 32, 4>;
using GRAY_14x14 = Texture<14, 14, 1>;

///////////////////////////////////////////////////////////

struct Textures
{
    com::POD_Array<RGBA_32x32, 10> sprites;
    com::POD_Array<GRAY_14x14, 128> font;
    void Load();
};

///////////////////////////////////////////////////////////

void Textures::Load()
{
    auto LoadFn = [](std::filesystem::path const& path, char* buffer, size_t size)
    {
        std::ifstream file { path, std::ios::binary };
        com::Assert(file.is_open(), "cannot open file");
        file.read(buffer, size);
    };


    std::vector<std::filesystem::path> paths;
    for(auto& it : std::filesystem::directory_iterator("res/Textures/Sprites/")) 
    {
        paths.emplace_back(it.path());
    }
    std::sort(paths.begin(), paths.end());
    for(auto& path : paths) 
    {
        auto& texture = sprites.Append();
        LoadFn(path, texture.buffer, texture.SIZE);
    }    
    paths.clear();

    for(auto& it : std::filesystem::directory_iterator("res/Textures/Font/EditorBold")) 
        paths.emplace_back(it.path());
    std::sort(paths.begin(), paths.end());
    for(auto& path : paths) 
    {
        auto& texture = font.Append();
        LoadFn(path, texture.buffer, texture.SIZE);
    }  
}

///////////////////////////////////////////////////////////

}//ns