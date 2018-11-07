#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

void sort(int *array, int len) {
  for(int i = 0; i < len - 1; i++) {
    for(int j = 0; j < len - i - 1; j++) {
      if (array[j] > array[j + 1]) {
	int tmp = array[j];
	array[j] = array[j + 1];
	array[j + 1] = tmp;
      }
    }
  }
}

void print(int *array, int len) {
  for(int i = 0; i < len; i++) {
    std::cout << array[i] << std::endl;
  }
}

static inline uint64_t rdtscp() {
  uint32_t aux;
  uint64_t rax,rdx;
  asm volatile ("rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux));
  return (rdx << 32) + rax;
}
//#define MEASURE_SYSCALL

int main(int argc, const char **argv) {
  static const int kLen = 1000;
  int *array = new int[kLen];
  srand(time(NULL));
  uint64_t t1 = rdtscp();
  for(int j = 0; j < 10000; j++) {
    for(int i = 0; i < kLen; i++) {
      array[i] = rand();
    }
#ifdef MEASURE_SYSCALL
    int fd = open("main.cc", O_RDONLY);
    if (fd < 0) {
      return 1;
    }
#endif
    sort(array, kLen);
#ifdef MEASURE_SYSCALL
    close(fd);
#endif
  }
  uint64_t t2 = rdtscp();
  std::cout << t2 - t1 << std::endl;
  delete[] array;
  return 0;
}
