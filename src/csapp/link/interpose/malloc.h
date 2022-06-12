#include<stddef.h>
#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)

void *mymalloc(unsigned int size);
void myfree(void* ptr);