gcc  -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl
gcc  -o intr int.c 
# 替代malloc有风险，因为很多函数都调用了它，在它内部不能使用有printf
LD_PRELOAD=./mymalloc.so ./intr