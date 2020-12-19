#pragma once

#include <charconv>
#include <iostream>

#include "com/Types.hpp"
#include "com/Assert.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

#define TEMPLATE template<auto N>
#define FOR_STRING(str, i) for(idx_t i = 0; i < str.length; ++i)

///////////////////////////////////////////////////////////

constexpr i32 StrLen(char const* ptr)
{
    i32 count = 0;
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
    char data [N] {};
    idx_t length = 0;
    
    String() = default;
    String(auto);
    void Append(auto&&);
    void operator=(auto);
    auto& operator[](idx_t);
    auto& operator[](idx_t) const;
    void Clear();

private:
    using COM_STRING = void*; //to identify this class when appending
    void AppendCString(chars_t);
    void AppendArithmetic(auto);
};

///////////////////////////////////////////////////////////

TEMPLATE
auto& String<N>::operator[](idx_t i)
{
    com::Assert(i < length, "string out of bounds");
    return data[i];
}

///////////////////////////////////////////////////////////

TEMPLATE
auto& String<N>::operator[](idx_t i) const
{
    com::Assert(i < length, "string out of bounds");
    return data[i];
}

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
void String<N>::Append(auto&& any)
{
    using T = std::decay_t<decltype(any)>;

    if constexpr(std::is_same_v<T, const char*>)
        AppendCString(any);

    if constexpr(std::is_arithmetic_v<T>)
        AppendArithmetic(any);

    if constexpr (requires { typename decltype(any)::COM_STRING; })
        AppendCString(any.data);
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
void String<N>::AppendArithmetic(auto arithmetic)
{
    auto capacity = N - length - 1;
    auto [end, res] = std::to_chars(data + length, data + capacity, arithmetic);
    com::Assert(res == std::errc(), "string conversion failed");
    auto delta = end - (data + length);
    length += delta;
    data[length] = '\0';
}

///////////////////////////////////////////////////////////

TEMPLATE
void String<N>::Clear()
{
    length = 0;
    data[0] = 0;
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