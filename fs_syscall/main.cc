#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdint.h>
using namespace std;

static inline uint64_t rdtscp() {
  uint32_t aux;
  uint64_t rax,rdx;
  asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
  return (rdx << 32) + rax;
}

int main(int argc, const char *argv[]) {
  char buf[1024];
  int fd = open("tmp", O_RDONLY);
  if (fd < 0) {
    perror("open:");
    return 1;
  }
  if (read(fd, buf, 1024) != 1024) {
    perror("read:");
    return 1;
  }
  if (lseek(fd, 0, 0) < 0) {
    perror("lseek:");
    return 1;
  }
  uint64_t t1 = rdtscp();
  for(int i = 0; i < 100; i++) {
    if (read(fd, buf, 1024) != 1024) {
      perror("read:");
      return 1;
    }
    if (lseek(fd, 0, 0) < 0) {
      perror("lseek:");
      return 1;
    }
  }
  uint64_t t2 = rdtscp();
  cout << t2 - t1 << endl;
  uint64_t t3 = rdtscp();
  for(int i = 0; i < 100; i++) {
    char buf2[1024];
    memcpy(buf2, buf, 1024);
  }
  uint64_t t4 = rdtscp();
  cout << t4 - t3 << endl;

  return 0;
}
