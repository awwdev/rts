@echo off
pushd %res%
mkdir %res%\\rgba
%magick%\\mogrify -format rgba -path "rgba" *.bmp
popd