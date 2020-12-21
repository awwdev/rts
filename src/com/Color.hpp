#pragma once

#include <iostream>
#include "com/Types.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

struct Col4n
{
    f32 r, g, b, a;

    auto Highlighted() const 
    {
        return Col4n
        { 
            com::Min(1, r + 0.15f), 
            com::Min(1, g + 0.15f), 
            com::Min(1, b + 0.15f), 
            a 
        };
    }
};

///////////////////////////////////////////////////////////

}//ns