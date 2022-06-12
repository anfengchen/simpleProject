#include "csapp.h"

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
void posix_error(int code, char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(0);
}
void gai_error(int code, char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}
void app_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}

ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    ssize_t num_read = 0;
    size_t num_left = n;
    char *bufptr = (char *)usrbuf;
    while (num_left > 0)
    {
        if ((num_read = read(fd, bufptr, num_left)) < 0)
        {
            if (errno == EINTR) // interrupted by a sig handler return
            {
                num_read = 0;
            }
            else
            {
                return -1;
            }
        }
        else if (num_read == 0) // EOF
        {
            break;
        }
        else
        {
            bufptr += num_read;
            num_left -= num_read;
        }
    }

    return n - num_left;
}
ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    ssize_t num_write = 0;
    size_t num_left = n;
    char *bufptr = usrbuf;

    while (num_left > 0)
    {
        if ((num_write = write(fd, bufptr, num_left)) < 0)
        {
            if (errno == EINTR) // interrupted by a sig handler return
            {
                num_write = 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            num_left -= num_write;
            bufptr += num_write;
        }
    }
    return n;
}

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    ssize_t cnt;
    while (rp->rio_cnt <= 0)
    {
        if ((rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf))) < 0)
        {
            if (errno != EINTR)
            {
                return -1;
            }
        }
        else if (rp->rio_cnt == 0)
        {
            return 0;
        }
        else
        {
            rp->rio_bufptr = rp->rio_buf;
        }
    }
    cnt = n < rp->rio_cnt ? n : rp->rio_cnt;

    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c;
    char *bufptr = (char *)usrbuf;

    for (n = 1; n < maxlen; ++n)
    {
        if ((rc = rio_read(rp, &c, 1)) == 1)
        {
            *bufptr++ = c;
            if (c == '\n')
            {
                n++;
                break;
            }
        }
        else if (rc == 0)
        {
            break;
        }
        else
        {
            return -1;
        }
    }
    bufptr = '\0';
    return n - 1;
}
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t num_left = n;
    ssize_t num_read = 0;
    char *bufptr = (char *)usrbuf;

    while (num_left > 0)
    {
        if ((num_read = rio_read(rp, bufptr, num_left)) < 0)
        {
            return -1;
        }
        else if (num_read == 0)
        {
            break;
        }
        else
        {
            num_left -= num_read;
            bufptr += num_read;
        }
    }

    return n - num_left;
}

int Stat(const char *filename, struct stat *buf)
{
    if (stat(filename, buf) < 0)
    {
        unix_error("Stat Error");
    }
    return 0;
}
int Fstat(int fd, struct stat *buf)
{
    if (fstat(fd, buf) < 0)
    {
        unix_error("Fstat Error");
    }
    return 0;
}

pid_t Fork(void)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        unix_error("Fork error");
    }
    return pid;
}

char *Fgets(char *str, int num, FILE *stream)
{
    char *ptr;
    if ((ptr = fgets(str, num, stream)) == NULL)
    {
        unix_error("Fgets error");
    }
    return ptr;
}

/*************************************************************
 * The Sio (Signal-safe I/O) package - simple reentrant output
 * functions that are safe for signal handlers.
 *************************************************************/
static size_t sio_strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        ++i;
    }

    return i;
}
static void sio_reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = sio_strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void sio_ltoa(long v, char s[], int b)
{
    int c, i = 0;
    int neg = v < 0;
    if (neg)
    {
        v = -v;
    }

    do
    {
        s[i++] = ((c = (v % b)) < 10) ? c + '0' : c - 10 + 'a';
        v = v / b;
    } while (v > 0);
    if (neg)
    {
        s[i++] = '-';
    }

    s[i] = '\0';
    sio_reverse(s);
}

ssize_t sio_puts(char s[])
{
    return write(STDOUT_FILENO, s, sio_strlen(s));
}
ssize_t sio_putl(long v)
{
    char s[128];
    sio_ltoa(v, s, 10);
    return sio_puts(s);
}
void sio_error(char s[])
{
    sio_puts(s);
    _exit(1);
}

sighandler_t Signal(int signum, sighandler_t handler)
{
    struct sigaction action, old_action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if (sigaction(signum, &action, &old_action) < 0)
    {
        unix_error("sigaction error");
    }

    return old_action.sa_handler;
}