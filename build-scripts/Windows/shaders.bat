pushd %src%
for /r %%i in (*) do glslc %%i -o %%i.spv
popd