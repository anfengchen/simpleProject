gcc -shared -fpic -o libvector.so addvec.c multvec.c
gcc -o prog1 main.c ./libvector.so
./prog1