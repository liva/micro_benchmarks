#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <sys/mman.h>

static inline uint64_t rdtscp() {
  uint32_t aux;
  uint64_t rax,rdx;
  asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
  return (rdx << 32) + rax;
}

void bench_array(char *buf, const int byte) {
  uint64_t t1 = rdtscp();
  for(int j = 0; j <= 64 * 1024 * 1024 * 30 / byte; j++) {
    for(int i = 0; i < byte; i+=64) {
      asm volatile("":: "a"(buf[i]));
    }
  }
  uint64_t t2 = rdtscp();
  std::cout << byte << "," << (t2 - t1) << std::endl;
}

int main(int argc, const char **argv) {
  int kMax = 64 * 1024 * 1024;
  char *buf = new char[kMax];
  //char *buf = (char *)mmap(NULL, kMax, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 , 0);
  for(int i = 0; i < kMax; i++) {
    buf[i] = i;
  }
  for(int i = 64; i <= kMax; i *= 2) {
    bench_array(buf, i);
  }
  return 0;
}
