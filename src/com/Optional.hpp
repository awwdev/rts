#pragma once

#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T>

///////////////////////////////////////////////////////////

TEMPLATE struct Optional
{
    bool hasValue;
    union 
    {
        struct {} uninit;
        T value;
    }
    data;

    Optional();
    Optional(auto const&... args);
    explicit operator bool() const { return hasValue; }
    T& Value() { return data.value; }
};

///////////////////////////////////////////////////////////

TEMPLATE Optional<T>::Optional()
    : hasValue { false }
    , data     { .uninit {} }
{}

///////////////////////////////////////////////////////////

TEMPLATE Optional<T>::Optional(auto const&... args)
    : hasValue { true }
    , data     { .value { args... } }
{}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns