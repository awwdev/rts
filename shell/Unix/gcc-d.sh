clear
mkdir -p $build_dir
mkdir -p $build_dir/res
cp -r -u $res_dir/* $build_dir/res

g++ --version
g++ \
-g \
-std=c++2a \
-Wall -Wextra -Wpedantic \
-Wno-unused-parameter \
-Wno-missing-field-initializers \
-Wno-unused-variable \
-I $src_hpp \
-I $ext_hpp \
-L $ext_lib \
$src_cpp \
-o $build_dir/$build_name \
-lX11 -lvulkan -lpthread