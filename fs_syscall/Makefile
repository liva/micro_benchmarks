define docker_wrapper
	docker run --rm -v ${PWD}:/workdir -w /workdir $2 $1 $3
endef
CONTAINER:=micro_benchmark_newlib

INCLUDE=$(shell $(call docker_wrapper,${CONTAINER},,gcc --print-file-name=include))

.PHONY: docker

default:

docker:
	docker build -t $(CONTAINER) docker

a.out: crt0.S main.c syscall.c
	$(call docker_wrapper,$(CONTAINER),,gcc -g -nostdinc -nostdlib -I $(INCLUDE) -I /newlib/x86_64-none-elf/include/ main.c syscall.c crt0.S -L /newlib/x86_64-none-elf/lib -lc)

b.out: main.c
	$(call docker_wrapper,$(CONTAINER),,gcc -g main.c -o b.out)

run: a.out
	$(call docker_wrapper,$(CONTAINER),,./a.out)

runb: b.out
	$(call docker_wrapper,$(CONTAINER),--cap-add=SYS_PTRACE --security-opt="seccomp=unconfined",strace ./b.out)

debug: a.out
	$(call docker_wrapper,$(CONTAINER),-it,sh -c "ulimit -c unlimited; ./a.out; gdb ./a.out core")

sh:
	$(call docker_wrapper,$(CONTAINER),-it,/bin/bash)

clean:
	rm -f a.out