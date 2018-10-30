#include <iostream>
#include <cstdint>

static inline uint32_t rdtscp() {
  uint32_t aux;
  uint64_t rax,rdx;
  asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
  return rax;
}

int main(int argc, const char **argv) {
  uint32_t t1 = rdtscp();
  uint32_t t2;
  asm volatile("syscall;":"=a"(t2):"a"(400): "cc", "rcx", "r11", "memory");
  uint32_t t3 = rdtscp();
  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;
  std::cout << t3 << std::endl;
  return 0;
}
