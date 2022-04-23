#define _XOPEN_SOURCE 800
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// error print
void unix_error(char *msg);
void posix_error(int code, char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);

/**********************************************************************
 * 健壮性IO
 * 主要提供了read、write的包装函数，其中read有缓存版本，而write没有
 * ********************************************************************/
/**
 * @brief read的包装函数，处理不足值的问题
 * 
 * @param fd 文件描述符
 * @param usrbuf 读取值的缓存位置
 * @param n 读取的字符数
 * @return ssize_t 成功：返回读取的长度，失败：-1
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n);

/**
 * @brief write的包装函数，会处理打断的错误
 * 
 * @param fd 文件描述符
 * @param usrbuf 写入值的缓存位置
 * @param n 读取的字符数
 * @return ssize_t 成功：返回读取的长度，失败：-1
 */
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

#define RIO_BUFSZIE 8192

/**
 * @brief 缓存版本用来描述流的数据结构
 * 是c语言标准io的简化版本
 */
typedef struct
{
    int rio_fd; // 文件描述符
    int rio_cnt; // 还未读取的字符数
    char *rio_bufptr; // 读取位置的迭代器
    char rio_buf[RIO_BUFSZIE]; // 缓存
} rio_t;

// 初始化函数，使用缓存版本之前要先调用
void rio_readinitb(rio_t *rp, int fd);
/**
 * @brief 读取一行，包含结尾符
 *
 * @param rp 健壮io的流描述符
 * @param usrbuf 数据保存的位置，包含'\0'
 * @param maxlen 包含结尾符'\0'的最大长度
 * @return ssize_t 读取的字符串的长度
 */
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/**
 * @brief 缓存版的读取n个字符，处理不足值和打断错误
 * 
 * @param rp 健壮io的流描述符
 * @param usrbuf 用来保存读取值的内存
 * @param n 目标读取的字符数
 * @return ssize_t 
 */
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

/************************************************************************
 * 包装函数
 * *********************************************************************/

int Stat(const char*filename, struct stat *buf);
int Fstat(int fd, struct stat *buf);