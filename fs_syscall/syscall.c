#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

void _exit(int status) { asm volatile("syscall;"::"a"(60)); while(1){} }
int close(int file) {}
char **environ; /* pointer to array of char * strings that define the current environment variables */
int execve(char *name, char **argv, char **env) {}
int fork(void) {}
int fstat(int file, struct stat *st) {}
int getpid(void) {}
int isatty(int file) {}
int kill(int pid, int sig) {}
int link(char *old, char *new) {}
int lseek(int file, int ptr, int dir) {}
int open(const char *name, int flags, ...) {}
int read(int file, char *ptr, int len) {}
caddr_t sbrk(int incr) {}
int stat(const char *file, struct stat *st) {}
clock_t times(struct tms *buf) {}
int unlink(char *name) {}
int wait(int *status) {}
int write(int file, char *ptr, int len) {}
int gettimeofday(struct timeval *p, void *z) {}
