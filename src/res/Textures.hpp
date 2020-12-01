#pragma once

#include <filesystem>
#include <fstream>
#include "com/Assert.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::res {

///////////////////////////////////////////////////////////

struct Textures
{
    static constexpr auto SIZE = 32*32*4;
    char buffer [SIZE];

    void Load();
};

///////////////////////////////////////////////////////////

void Textures::Load()
{
    chars_t path = "res/Textures/rgba/test.rgba";
    std::ifstream file { path, std::ios::binary };
    com::Assert(file.is_open(), "cannot open file");
    file.read(buffer, SIZE);
}

///////////////////////////////////////////////////////////

}//ns