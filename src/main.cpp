#include "wnd/Window.hpp"
#include "com/Console.hpp"

using namespace mini;

int main()
{
    com::SetupConsole();
    com::MoveConsole(64, 400 + 64, 600, 400);
    wnd::Window window { "mini window", 600, 400, 64, 64 };

    while(true)
    {
        window.PollEvents();
    }
}