define docker_wrapper
	docker run --rm -v ${PWD}:/workdir -w /workdir $1 $2
endef
CONTAINER:=livadk/newlib:15f36c6e9ef1e02e16339588794ed0ae1d1a1bda

INCLUDE=$(shell $(call docker_wrapper,${CONTAINER},gcc --print-file-name=include))

default:

run:
	$(call docker_wrapper,$(CONTAINER),gcc -nostdinc -nostdlib -I $(INCLUDE) -I /newlib/x86_64-none-elf/include/ main.c syscall.c crt0.S -L /newlib/x86_64-none-elf/lib -lc)
	$(call docker_wrapper,$(CONTAINER),./a.out)

clean:
	rm -f a.out