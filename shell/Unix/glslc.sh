mkdir $res/spv
pushd $glslc
for file in $res/*.*; do
    ./glslc -std=450 $file -o $file.spv
    mv $file.spv $res/spv/
done    
popd