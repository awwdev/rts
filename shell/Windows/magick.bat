@echo off
pushd %Textures%
mkdir %Textures%\\sprites
%magick%\\mogrify -set colorspace RGB -format rgba -path "sprites" *.png
popd