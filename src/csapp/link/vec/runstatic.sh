# 创建静态库
gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o

# 编译程序并执行
gcc -c main.c
gcc -static -o prog main.o -L. -lvector
./prog