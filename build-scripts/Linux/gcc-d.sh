clear
mkdir $build_dir

g++ --version
g++ \
-g \
-std=c++2a \
-Wall -Wextra -Wpedantic \
-I $src_hpp \
$src_cpp \
-o $build_dir$build_name