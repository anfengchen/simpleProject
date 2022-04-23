/**
 * @file apue.h
 * @author your name (you@domain.com)
 * @brief Our own header ,to be include before all standard system headers
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _APUE_H
#define _APUE_H

#define _POSIX_C_SOURCE 200809L

#if defined(SOLARIS) // Solaris 10
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 700
#endif

#include <sys/stat.h>
#include <sys/termios.h> // for winsize
#include <sys/types.h>

#if defined(MACOS) || !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096

// default file access permissions for new files
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// default permissions for new directions
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef void Sigfunc(int); // for signal hanlders

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// Prototypes for our own functions
char *path_alloc(size_t *);

/**
 * @brief Nonfatal error unrelated to a system call
 * Print a message and return
 * 
 * @param fmt 
 * @param ... 
 */
void err_msg(const char *fmt, ...);

/**
 * @brief Fatal error related to a system call
 * Print a message, dump core, and terminate
 * 
 * @param fmt 
 * @param ... 
 */
void err_dump(const char * fmt, ...) __attribute__((noreturn));

/**
 * @brief Fatal error unrelated to a system call
 * Print a message and terminate
 * 
 * @param fmt 
 * @param ... 
 */
void err_quit(const char * fmt, ...) __attribute__((noreturn));

/**
 * @brief Nonfatal error unrelated to a system call
 * Error code passed as explict parameter.
 * Print a message and return.
 * @param error Error code
 * @param fmt
 * @param ...
 */
void err_cont(int error,const char* fmt,...);

/**
 * @brief Nonfatal error unrelated to a system call
 * Error code passed as explict parameter.
 * Print a message and terminate.
 * @param error Error code
 * @param fmt
 * @param ...
 */
void err_exit(int error,const char* fmt,...) __attribute__((noreturn));
/**
 * @brief Nofatal error related to a system call
 * Print a massage and return.
 * 
 * @param fmt 
 * @param ... 
 */
void err_ret(const char* fmt,...);

/**
 * @brief Fatal error related to system call
 * Print a massage and terminate.
 * @param fmt 
 * @param ... 
 */
void err_sys(const char*fmt,...) __attribute__((noreturn));

void log_msg(const char*,...);
void log_open(const char*,int,int)__attribute__((noreturn));
void log_quit(const char* ,...) __attribute__((noreturn));
void log_exit(int,const char*,...) __attribute__((noreturn));
void log_ret(const char*,...);
void log_sys(const char*,...) __attribute__((noreturn));


#endif
