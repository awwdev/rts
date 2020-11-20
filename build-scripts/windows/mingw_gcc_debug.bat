cls
@echo off
mkdir %build_dir%

Pushd %compiler_dir%
g++ --version
g++ ^
-g ^
-std=c++2a ^
-Wall -Wextra -Wpedantic ^
%src_cpp% ^
-I %src_hpp% ^
-I %ext_hpp% ^
-L %ext_lib% ^
-o %build_dir%%build_name% ^
-static ^
-lvulkan-1 -lgdi32 -lws2_32 -lwinmm
popd