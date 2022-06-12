#ifdef COMPILETIME
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
void *mymalloc(size_t size)
{
    void *ptr = malloc(size);
    printf("malloc(%ld)=%p\n", size, ptr);
    return ptr;
}

void myfree(void *ptr)
{
    free(ptr);
    printf("free(%p)\n", ptr);
}
#endif

#ifdef LINKTIME
#include <stddef.h>
#include <stdio.h>
void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size)
{
    void *ptr = __real_malloc(size);
    printf("malloc(%ld)=%p\n", size, ptr);
    return ptr;
}

void __wrap_free(void *ptr)
{
    __real_free(ptr);
    printf("free(%p)\n", ptr);
}

#endif

#ifdef RUNTIME

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    // fprintf使用stderr没有问题，使用printf有问题
    fprintf(stderr,"size=%ld\n", size); 
    void *(*mallocp)(size_t size);
    char *error;

    mallocp = dlsym(RTLD_NEXT, "malloc");
    if ((error = dlerror()) != NULL)
    {
        fputs(error, stderr);
        exit(1);
    }

    void *ptr = mallocp(size);
    fprintf(stderr,"malloc(%ld)=%p\n", size, ptr);
    return ptr;
}

void free(void *ptr)
{
    void (*freep)(void *ptr) = NULL;
    char *error;

    freep = dlsym(RTLD_NEXT, "free");
    if ((error = dlerror()) != NULL)
    {
        fputs(error, stderr);
        exit(1);
    }

    freep(ptr);

    fprintf(stderr,"free(%p)\n", ptr);
}

#endif
