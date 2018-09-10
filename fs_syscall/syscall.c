// 参考：
// https://www.mztn.org/lxasm64/x86_x64_table.html
// https://main.lv/writeup/gcc_inline_assembly.md
// https://stackoverflow.com/questions/9506353/how-to-invoke-a-system-call-via-sysenter-in-inline-assembly
// System V Application Binary Interface AMD64 Architecture Processor Supplement
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
int getpid(void) {
  int rval;
  asm volatile("syscall;":"=a"(rval):"a"(39): "cc", "rcx", "r11", "memory");
  if (rval < 0) {
    return -1;
  }
  return rval;
}
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
int write(int file, char *ptr, int len) {
  if (file == 1) {
    int rval;
    asm volatile("syscall;":"=a"(rval):"a"(1),"D"(file),"S"(ptr),"d"(len): "cc", "rcx", "r11", "memory");
    if (rval < 0) {
      return -1;
    } else {
      return rval;
    }
  } else {
    return -1;
  }
}
int gettimeofday(struct timeval *p, void *z) {}
