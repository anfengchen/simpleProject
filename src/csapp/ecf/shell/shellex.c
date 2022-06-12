#include "csapp.h"

#define MAXARGS 128
#define MAXLINE 1024

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int buildin_command(char **argv);

int main()
{
    char cmdline[MAXLINE];

    while (1)
    {
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
        {
            exit(0);
        }

        eval(cmdline);
    }
}

void eval(char *cmdline)
{
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
    {
        return;
    }

    if (!buildin_command(argv))
    {
        // 子线程，运行execve则不再返回
        if ((pid = Fork()) == 0)
        {
            if (execve(argv[0], argv, environ) < 0)
            {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        if (!bg)
        {
            if (waitpid(pid, NULL, 0) < 0)
            {
                unix_error("waitfg: waitpid error");
            }
            else
            {
                printf("%d %s", pid, cmdline);
            }
        }
    }
    return;
}

/**
 * @brief 将buf分解成参数argv的形式
 *
 * @param buf 命令行
 * @param argv 参数数组，用于返回
 * @return int 0 为正常程序， 1 为后台程序或空行
 */
int parseline(char *buf, char **argv)
{
    char *delim;
    int argc = 0;
    int bg;

    buf[strlen(buf) - 1] = ' '; // Replace trailing '\n' with space
    while (*buf && (*buf == ' '))
    {
        buf++;
    }

    while ((delim = strchr(buf, ' ')) != NULL)
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' '))
        {
            buf++;
        }
    }

    argv[argc] = NULL;

    if (argc == 0)
        return 1;
    if ((bg = (*argv[argc - 1] == '&')) != 0)
    {
        argv[--argc] = NULL;
    }
    return bg;
}

/**
 * @brief 处理内置命令，内置命令运行它并返回true
 * 目前只支持quit
 *
 * @param argv 入参，调用程序的参数列表
 * @return int 1为内置命令，0为可执行文件
 */
int buildin_command(char **argv)
{
    if (!strcmp(argv[0], "quit"))
    {
        exit(0);
    }

    if (!strcmp(argv[0], "&")) // Ignore singleton
    {
        return 1;
    }
    return 0;
}
