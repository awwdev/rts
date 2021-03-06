#pragma once

#include "res/Textures.hpp"

///////////////////////////////////////////////////////////

namespace rts::res {

///////////////////////////////////////////////////////////

struct Resources
{
    Textures textures;

    Resources();
};

///////////////////////////////////////////////////////////

Resources::Resources()
{
    textures.Load();
}

///////////////////////////////////////////////////////////

}//ns