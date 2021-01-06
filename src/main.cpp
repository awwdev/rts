#ifdef _WIN32
#   include "WinMain.hpp"
#endif

#ifdef __linux__
#   include "UnixMain.hpp"
#endif

int main(int argc, char** argv)
{
    using namespace rts::app;
    CmdArgs cmdArgs { argc, argv };
    AppMain(cmdArgs);
}