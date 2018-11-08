  .text
	  .globl _start
_start:
	mov %rsp, %rbp
	mov 0(%rbp), %rdi
	mov 8(%rbp), %rsi
	call main
	mov %rax, %rdi
	mov $60, %rax
	syscall
	//call exit
