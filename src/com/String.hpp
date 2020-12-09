#pragma once

#include <charconv>
#include <iostream>

#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<auto N>

///////////////////////////////////////////////////////////

constexpr idx_t StrLen(char const* ptr)
{
    idx_t count = 0;
    while(*ptr != '\0') 
    {
        count++;
        ptr++;
    }
    return count;  
}

///////////////////////////////////////////////////////////

TEMPLATE
struct String
{
    using COM_STRING = void*;

    char data [N] {};
    idx_t length = 0;
    
    String() = default;
    String(auto);
    void Append(auto);
    void operator=(auto);

private:
    void AppendCString(chars_t);
    void AppendArithmetic(auto);
    void AppendComString(auto);
};

///////////////////////////////////////////////////////////

TEMPLATE
String<N>::String(auto any)
{
    Append(any);
}

///////////////////////////////////////////////////////////

TEMPLATE
void String<N>::operator=(auto any)
{
    length = 0;
    Append(any);
}

///////////////////////////////////////////////////////////

TEMPLATE
void String<N>::Append(auto any)
{
    using T = decltype(any);

    if constexpr(std::is_same_v<T, const char*>)
        AppendCString(any);

    if constexpr(std::is_arithmetic_v<T>)
        AppendArithmetic(any);

    if constexpr (requires { typename decltype(any)::COM_STRING; })
        AppendComString(any);
}

///////////////////////////////////////////////////////////

TEMPLATE
void String<N>::AppendCString(chars_t src)
{
    auto len = StrLen(src);
    com::Assert(length + len < N, "string exhausted");
    std::memcpy(data + length, src, len);
    length += len;
    data[length] = '\0';
}

///////////////////////////////////////////////////////////

TEMPLATE
void String<N>::AppendArithmetic(auto src)
{
    auto capacity = N - length - 1;
    auto [end, res] = std::to_chars(data + length, data + capacity, src);
    com::Assert(res == std::errc(), "string conversion failed");
    auto delta = end - (data + length);
    length += delta;
    data[length] = '\0';
}

///////////////////////////////////////////////////////////

TEMPLATE
void String<N>::AppendComString(auto src)
{
    AppendCString(src.data);
}

///////////////////////////////////////////////////////////

TEMPLATE
std::ostream& operator<<(std::ostream& os, String<N> const& str)
{
    os << str.data;
    return os;
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

}//ns