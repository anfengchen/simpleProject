# !bash
arg=${1}

rm *.i *.o *.s main
# 生成可重定位目标函数
#-I /usr/include/c++/ 
# -std=gnu++11
# 预处理
g++ -I ./ -g -E main.cpp > main.i
# 编译
g++  -I ./ -g -S ./*.cpp 
# 汇编可重定位目标文件
g++ -I ./ -g -c ./*.cpp

if [ $arg = 'dynamic' ]
then
#生成动态库
    g++ -shared -fPIC -o n_maxSubSum.so n_maxSubSum.cpp
    g++ -o main main.o n_maxSubSum.so
    export  LD_LIBRARY_PATH=./
    echo "run MaxSubSum time complexity O(n): "
    ./main
elif [ $arg = 'static' ]
then
    echo "run MaxSubSum time complexity O(n^2): "
    g++ -o main main.o n2_maxSubSum.o
    ./main
else
    echo "run MaxSubSum time complexity O(nlogn): "
    g++ -o main main.o nlogn_maxSubSum.o
    ./main
fi
