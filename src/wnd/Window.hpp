#pragma once

#ifdef _WIN32
#include "Window_Win32.hpp"
#endif

#ifdef __linux__
#include "Window_X11.hpp"
#endif