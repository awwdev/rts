#pragma once

#include "com/Types.hpp"
#include "com/Assert.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T, auto N>
#define FOR_ARRAY(arr, i) for(idx_t i = 0; i < arr.count; ++i)

///////////////////////////////////////////////////////////

TEMPLATE 
struct POD_Array
{
    idx_t count = 0;
    T data [N];

    POD_Array() = default;
    POD_Array(auto const&...);
    auto& Append(auto const&...);

    template<typename T2, auto N2>
    void AppendArray(POD_Array<T2, N2> const& other)
    {
        FOR_ARRAY(other, i)
        {
            auto& element = other[i];
            Append(element);
        }
    }

    auto& operator[](idx_t);
    auto& operator[](idx_t) const;

    T* Contains(T const&);
    auto& Pop();
};

///////////////////////////////////////////////////////////

TEMPLATE 
auto& POD_Array<T, N>::operator[](idx_t i)
{
    com::Assert(i < count, "array access out of bounds");
    return data[i];
}

///////////////////////////////////////////////////////////

TEMPLATE 
auto& POD_Array<T, N>::operator[](idx_t i) const
{
    com::Assert(i < count, "array access out of bounds");
    return data[i];
}

///////////////////////////////////////////////////////////

TEMPLATE 
auto& POD_Array<T, N>::Append(auto const&... args)
{
    com::Assert((count + 1) <= N, "array exhausted");
    data[count] = { args... };
    count += 1;
    return data[count - 1];
}

///////////////////////////////////////////////////////////

TEMPLATE 
POD_Array<T, N>::POD_Array(auto const&... elements)
    : count { sizeof...(elements) }
    , data  { elements... }
{
    com::Assert(count <= N, "array exhausted");
}

///////////////////////////////////////////////////////////

template<typename T, class... Ts>
POD_Array(T, Ts...) -> POD_Array<T, sizeof...(Ts) + 1>;

///////////////////////////////////////////////////////////

TEMPLATE 
T* POD_Array<T, N>::Contains(T const& other)
{
    FOR_ARRAY((*this), i)
    {
        auto& element = this->operator[](i);
        if (element == other)
            return &element;
    }
    return nullptr;
}

///////////////////////////////////////////////////////////

TEMPLATE 
auto& POD_Array<T, N>::Pop()
{
    com::Assert(count > 0, "array access out of bounds");
    count--;
    return data[count];
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns