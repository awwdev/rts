#pragma once

#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T, auto N>
#define FOR_SIMPLE_ARRAY(arr, i) for(idx_t i = 0; i < arr.count; ++i)

///////////////////////////////////////////////////////////

TEMPLATE struct SimpleArray
{
    T data [N];
    idx_t count = 0;

    auto& operator[](idx_t);
    auto& operator[](idx_t) const;

    void Append(auto... args);
};

///////////////////////////////////////////////////////////

TEMPLATE auto& SimpleArray<T, N>::operator[](idx_t i)
{
    com::Assert(i < count, "index out of array bounds");
    return data[i];
}

////////////////////////////////////////////////////////////

TEMPLATE auto& SimpleArray<T, N>::operator[](idx_t i) const
{
    com::Assert(i < count, "index out of array bounds");
    return data[i];
}

///////////////////////////////////////////////////////////

TEMPLATE void SimpleArray<T, N>::Append(auto... args)
{
    com::Assert((count + 1) < N, "array exhausted");
    data[count] = { args... };
    count += 1;
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns