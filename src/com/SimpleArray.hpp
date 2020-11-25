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
    idx_t count = 0;
    T data [N];

    SimpleArray() = default;
    SimpleArray(auto... elements);

    auto& operator[](idx_t);
    auto& operator[](idx_t) const;

    void Append(auto... args);
    T* Contains(T const&);
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

TEMPLATE SimpleArray<T, N>::SimpleArray(auto... elements)
    : count { sizeof...(elements) }
    , data  { elements... }
{
    com::Assert(count <= N, "array exhausted");
}

////////////////////////////////////////////////////////////

template<typename T, class... Ts>
SimpleArray(T, Ts...) -> SimpleArray<T, sizeof...(Ts) + 1>;

////////////////////////////////////////////////////////////

TEMPLATE T* SimpleArray<T, N>::Contains(T const& other)
{
    FOR_SIMPLE_ARRAY((*this), i)
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