int write(int fd, char *ptr, int len) {
  int rval;
  asm volatile("syscall;":"=a"(rval):"a"(1),"D"(fd),"S"(ptr),"d"(len): "cc", "rcx", "r11", "memory");
  return rval;
}

int open(const char *fname, int flags, int mode) {
  int rval;
  asm volatile("syscall;":"=a"(rval):"a"(2),"D"(fname),"S"(flags),"d"(mode): "cc", "rcx", "r11", "memory");
  return rval;
}

using size_t = __UINT64_TYPE__;
using off_t = __INT64_TYPE__;
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
  void *rval;
  asm volatile("movq %5, %%r10; movq %6, %%r8; movq %7, %%r9; syscall;":"=a"(rval):"a"(9),"D"(addr),"S"(length),"d"(prot),"r"((__UINT64_TYPE__)flags),"r"((__INT64_TYPE__)fd),"r"((__INT64_TYPE__)offset): "cc", "rcx", "r11", "r10", "r9", "r8", "memory");
  return rval;
}

// using sigset_t = unsigned long;

// // from glibc-2.28 bits/types/siginfo_t.h
// typedef struct
// {
//   int si_signo;               /* Signal number.  */
//   int si_errno;               /* If non-zero, an errno value associated with                                                                                                                                                                                                  
// 				 this signal, as defined in <errno.h>.  */
//   int si_code;                /* Signal code.  */
//   __pid_t si_pid;             /* Sending process ID.  */
//   __uid_t si_uid;             /* Real user ID of sending process.  */
//   void *si_addr;              /* Address of faulting instruction.  */
//   int si_status;              /* Exit value or signal.  */
//   long int si_band;           /* Band event for SIGPOLL.  */
//   __sigval_t si_value;        /* Signal value.  */
// } siginfo_t;

// struct sigaction {
//   void     (*sa_handler)(int);
//   void     (*sa_sigaction)(int, siginfo_t *, void *);
//   sigset_t   sa_mask;
//   int        sa_flags;
//   void     (*sa_restorer)(void);
// };

// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
//   int rval;
//   asm volatile("syscall;":"=a"(rval):"a"(),"D"(signum),"S"(act),"d"(oldact): "cc", "rcx", "r11", "memory");
//   return rval;
// }

#define O_RDWR (0x2)
#define MAP_SHARED (0x1)
#define MAP_FIXED (0x10)
#define PROT_READ (0x1)
#define PROT_WRITE (0x2)
#define PROT_EXEC (0x4)
#define PROT_NONE (0x0)

extern "C" int main() {
  char *mes = "hello\n";
  write(1, mes, sizeof(mes) - 1);

  int fd = open("mem_file", O_RDWR, 0);

  mmap((void *)0x300000, 0x1000, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_SHARED | MAP_FIXED, fd, 0);
  *((char *)0x300000) = 1;

  return 0;
}
