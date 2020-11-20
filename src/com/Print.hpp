#pragma once
#include <iostream>

namespace min::com {

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

inline void PrintColored(ConsoleColor col, auto... args)
{
#ifdef _WIN32
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
#endif

    ((std::cout << args << ' '), ...);

#ifdef _WIN32
    std::cout << "\x1b[0m"; //reset
#endif

    std::cout << '\n';
}

//? basic

inline void Print(auto... args)
{
    PrintColored(ConsoleColor::White, args...);
}

inline void PrintError(auto... args)
{
    PrintColored(ConsoleColor::Red, args...);
}

inline void PrintWarning(auto... args)
{
    PrintColored(ConsoleColor::Yellow, args...);
}

//? specialized

inline void PrintBool(bool expr, const char* msg, auto... args)
{
    PrintColored(expr ? ConsoleColor::Green : ConsoleColor::Red, msg, args...);
}

}//ns