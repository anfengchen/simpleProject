#include "csapp.h"
#define MAXBUF 1024

volatile sig_atomic_t times = 0;
void handler(int sig)
{
    int olderrno = errno;
    int t = times + 1;
    times = t;
    sio_putl((long)times);
    while ((waitpid(-1, NULL, WNOHANG)) > 0)
    {
        sio_puts("Handler reaped child\n");
    }

    if (errno && errno != ECHILD)
    {
        sio_error("waitpid error");
    }

    // sleep(1);
    errno = olderrno;
}

int main()
{
    int i, n;
    char buf[MAXBUF];

    if (Signal(SIGCHLD, handler) == SIG_ERR)
    {
        unix_error("signal error");
    }

    for (i = 0; i < 5; i++)
    {
        if (Fork() == 0)
        {
            printf("Hello from child %d\n", (int)getpid());
            sleep(i + 1);
            exit(0);
        }
    }

    if (n = read(STDIN_FILENO, buf, sizeof(buf)) < 0)
    {
        unix_error("read error");
    }

    printf("Parent process input\n");
    while (1)
        ;
    exit(0);
}
