@echo off
pushd %res%
mkdir %res%\\spv
for /r %%i in (*.frag, *.vert) do glslc %%i -o %%i.spv
for /r %%i in (*.spv) do move %%i %res%spv
popd