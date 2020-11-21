#pragma once

#include <iostream>

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

enum class ConsoleColor
{
    White,
    Cyan,
    Yellow,
    Green,
    Red,
    Blue,
    Magenta,
};

///////////////////////////////////////////////////////////

inline void Win32_SetColor(ConsoleColor col)
{
    //TODO using enum
    switch(col)
    {
        case ConsoleColor::Red:      std::cout << "\x1b[91m"; break;
        case ConsoleColor::Green:    std::cout << "\x1b[92m"; break;
        case ConsoleColor::Yellow:   std::cout << "\x1b[93m"; break;
        case ConsoleColor::Blue:     std::cout << "\x1b[94m"; break;
        case ConsoleColor::Magenta:  std::cout << "\x1b[95m"; break;
        case ConsoleColor::Cyan:     std::cout << "\x1b[96m"; break;
        case ConsoleColor::White: break;
        default: break;
    }
}

///////////////////////////////////////////////////////////

inline void X11_SetColor(ConsoleColor col)
{
    //TODO using enum
    switch(col)
    {
        case ConsoleColor::Red:      std::cout << "\x1B[31m"; break;
        case ConsoleColor::Green:    std::cout << "\x1B[32m"; break;
        case ConsoleColor::Yellow:   std::cout << "\x1B[33m"; break;
        case ConsoleColor::Blue:     std::cout << "\x1B[34m"; break;
        case ConsoleColor::Magenta:  std::cout << "\x1B[35m"; break;
        case ConsoleColor::Cyan:     std::cout << "\x1B[36m"; break;
        case ConsoleColor::White: break;
        default: break;
    }
}

///////////////////////////////////////////////////////////

inline void Win32_ResetColor()
{
    std::cout << "\x1b[0m";
}

///////////////////////////////////////////////////////////

inline void X11_ResetColor()
{
    std::cout << "\033[0m";
}

///////////////////////////////////////////////////////////

inline void PrintColored(ConsoleColor col, auto... args)
{
    #ifdef _WIN32
    Win32_SetColor(col);
    #endif

    #ifdef __linux__
    X11_SetColor(col);
    #endif

    ((std::cout << args << ' '), ...);

    #ifdef _WIN32
    Win32_ResetColor();
    #endif

    #ifdef __linux__
    X11_ResetColor();
    #endif

    std::cout << '\n';
}

///////////////////////////////////////////////////////////

inline void Print(auto... args)
{
    PrintColored(ConsoleColor::White, args...);
}

///////////////////////////////////////////////////////////

inline void PrintError(auto... args)
{
    PrintColored(ConsoleColor::Red, args...);
}

///////////////////////////////////////////////////////////

inline void PrintWarning(auto... args)
{
    PrintColored(ConsoleColor::Yellow, args...);
}

///////////////////////////////////////////////////////////

inline void PrintBool(bool expr, const char* msg, auto... args)
{
    PrintColored(expr ? ConsoleColor::Green : ConsoleColor::Red, msg, args...);
}

///////////////////////////////////////////////////////////

}//ns