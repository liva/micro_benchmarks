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

extern "C" int main() {
  char *mes = "hello\n";
  write(1, mes, sizeof(mes) - 1);

  int fd = open("mem_file", 0x2, 0);

  mmap((void *)0x300000, 0x1000, 0x4 | 0x2 | 0x1, 0x1 | 0x10, fd, 0);
  *((char *)0x300000) = 1;

  return 0;
}
