define docker_wrapper
	docker run --rm -v ${PWD}:/workdir -w /workdir $2 $1 $3
endef
CONTAINER:=livadk/newlib:73983144db760e5c2623e89d801e3b2f74976f47

INCLUDE=$(shell $(call docker_wrapper,${CONTAINER},,gcc --print-file-name=include))

default:

a.out: crt0.S main.c syscall.c
	$(call docker_wrapper,$(CONTAINER),,gcc -g -nostdinc -nostdlib -I $(INCLUDE) -I /newlib/x86_64-none-elf/include/ main.c syscall.c crt0.S -L /newlib/x86_64-none-elf/lib -lc)

run: a.out
	$(call docker_wrapper,$(CONTAINER),,./a.out)

debug: a.out
	$(call docker_wrapper,$(CONTAINER),-it,sh -c "ulimit -c unlimited; ./a.out; gdb ./a.out core")

sh:
	$(call docker_wrapper,$(CONTAINER),-it,/bin/bash)

clean:
	rm -f a.out