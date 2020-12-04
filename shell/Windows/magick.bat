@echo off
pushd %res%
mkdir %res%\\rgba
%magick%\\mogrify -set colorspace RGB -format rgba -path "rgba" *.png
popd