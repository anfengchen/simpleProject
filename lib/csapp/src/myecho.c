#include "csapp.h"

int main(int argc, char *argv[], char *envp[])
{
    char **ptrToArgv = argv;
    char **ptrToEnvp = envp;
    int i = 0;
    printf("Command-line arguments:\n");
    while (*ptrToArgv != NULL)
    {
        printf("\targv[%02d]: %s\n", i++, *ptrToArgv++);
    }

    i = 0;
    printf("Environment variables:\n");
    while (*ptrToEnvp != NULL)
    {
        printf("\targv[%02d]: %s\n", i++, *ptrToEnvp++);
    }

    return 0;
}