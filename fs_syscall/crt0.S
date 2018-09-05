  .text
	  .globl _start
_start:	 # _start is the entry point known to the linker
	  mov %rsp, %rbp  # setup a new stack frame
	  mov 0(%rbp), %rdi # get argc from the stack
	  mov 8(%rbp), %rsi # get argv from the stack
	  call main     # %rdi, %rsi are the first two args to main
	  mov %rax, %rdi  # mov the return of main to the first argument
	  call exit