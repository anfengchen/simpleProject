#include "csapp.h"

int main(int argc, char **argv)
{
    struct stat stat_buf;
    char *type, *readok;
    Stat(argv[1], &stat_buf);

    if (S_ISREG(stat_buf.st_mode))
    {
        type = "regular";
    }
    else if (S_ISDIR(stat_buf.st_mode))
    {
        type = "directory";
    }
    else
    {
        type = "other";
    }

    if ((stat_buf.st_mode & S_IRUSR))
    {
        readok = "yes";
    }
    else
    {
        readok = "no";
    }

    printf("%s: type: %s, read: %s\n", argv[1], type, readok);
}