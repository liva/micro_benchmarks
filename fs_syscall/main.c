#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>

int main() {
  int i;
  asm volatile("mov    %%fs:0x28,%%rax":"=a"(i));
  printf("hoge");
  //puts("Hello World!");
  //write(1, "aa\n", 3);
  //putchar('\n');
  //getpid();
  return 0;
}
