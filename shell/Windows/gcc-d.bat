cls
@echo off
mkdir %build_dir%
mkdir %build_dir%res
xcopy /s /y /d %res_dir%* %build_dir%res\\*
echo.

Pushd %compiler_dir%
g++ --version
echo.

g++ ^
-g ^
-mwindows ^
-std=c++2a ^
-Wall -Wextra -Wpedantic ^
-Wno-unused-parameter ^
-Wno-unused-function ^
-Wno-unused-variable ^
-Wno-unused-but-set-variable ^
-Wno-unused-local-typedefs ^
-I %src_hpp% ^
-I %ext_hpp% ^
-L %ext_lib% ^
%src_cpp% ^
-o %build_dir%%build_name% ^
-static ^
-lvulkan-1 -lgdi32 -lws2_32 -lwinmm

popd