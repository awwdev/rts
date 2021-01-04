#pragma once

#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

template<typename T>
struct Optional
{
    bool hasData;
    union 
    {
        struct {} uninit;
        T data;
    }
    unionData;

    Optional();
    Optional(auto const&... args);
    explicit operator bool() const { return hasData; }
    T& Data() { return unionData.data; }
    auto& operator*() { return unionData.data; }
};

///////////////////////////////////////////////////////////

template<typename T>
Optional<T>::Optional()
    : hasData   { false }
    , unionData { .uninit {} }
{}

///////////////////////////////////////////////////////////

template<typename T>
Optional<T>::Optional(auto const&... args)
    : hasData   { true }
    , unionData { .data { args... } }
{}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns