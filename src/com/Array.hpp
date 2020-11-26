#pragma once

#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T, auto N>
#define FOR_ARRAY(arr, i) for(idx_t i = 0; i < arr.count; ++i)

///////////////////////////////////////////////////////////

TEMPLATE struct Array
{
    idx_t count = 0;
    T data [N];

    Array() = default;
    Array(auto... elements);

    auto& operator[](idx_t);
    auto& operator[](idx_t) const;

    void Append(auto... args);
    T* Contains(T const&);
};

///////////////////////////////////////////////////////////

TEMPLATE auto& Array<T, N>::operator[](idx_t i)
{
    com::Assert(i < count, "index out of array bounds");
    return data[i];
}

////////////////////////////////////////////////////////////

TEMPLATE auto& Array<T, N>::operator[](idx_t i) const
{
    com::Assert(i < count, "index out of array bounds");
    return data[i];
}

///////////////////////////////////////////////////////////

TEMPLATE void Array<T, N>::Append(auto... args)
{
    com::Assert((count + 1) < N, "array exhausted");
    data[count] = { args... };
    count += 1;
}

///////////////////////////////////////////////////////////

TEMPLATE Array<T, N>::Array(auto... elements)
    : count { sizeof...(elements) }
    , data  { elements... }
{
    com::Assert(count <= N, "array exhausted");
}

////////////////////////////////////////////////////////////

template<typename T, class... Ts>
Array(T, Ts...) -> Array<T, sizeof...(Ts) + 1>;

////////////////////////////////////////////////////////////

TEMPLATE T* Array<T, N>::Contains(T const& other)
{
    FOR_ARRAY((*this), i)
    {
        auto& element = this->operator[](i);
        if (element == other)
            return &element;
    }
    return nullptr;
}

////////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns