clear
mkdir $build_dir
mkdir $exe_path

pushd /usr/bin/
g++-10 --version
g++-10 \
-g \
-std=c++2a \
-Wall -Wextra -Wpedantic \
$src_cpp \
-I $src_hpp \
-o $build_dir$build_name
popd