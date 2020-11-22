clear
mkdir $build_dir

g++ --version
g++ \
-g \
-std=c++2a \
-Wall -Wextra -Wpedantic \
-I $src_hpp \
-I $ext_hpp \
-L $ext_lib \
$src_cpp \
-o $build_dir$build_name \
-lX11 -lvulkan