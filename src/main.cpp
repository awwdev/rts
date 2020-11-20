#include "wnd/Window.hpp"
#include "com/Console.hpp"

int main()
{
    min::com::SetupConsole();
    min::com::MoveConsole(64, 400 + 64, 600, 400);

    min::wnd::Window window { "mini window", 600, 400, 64, 64 };
    window.Display();

    while(min::wnd::running)
    {
        window.PollEvents();
    }
}