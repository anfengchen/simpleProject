#include "csapp.h"

volatile sig_atomic_t pid;

void sigchild_handler(int s)
{
    int olderrno = errno;
    waitpid(-1, NULL, 0);
    errno = olderrno;
}

void sigint_handler(int s) {}

int main(int argc, char *argv[])
{
    sigset_t mask, prev;

    Signal(SIGCHLD, sigchild_handler);
    Signal(SIGINT, sigint_handler);
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);

    while (1)
    {
        sigprocmask(SIG_BLOCK, &mask, &prev);
        if (Fork() == 0)
        {
            exit(0);
        }

        pid = 0;
        while (!pid)
        {
            sigsuspend(&prev);
        }

        sigprocmask(SIG_SETMASK, &prev, NULL);
        printf(".");
    }
    exit(0);
}