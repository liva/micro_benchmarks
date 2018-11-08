.PHONY: docker

default: mem_file
	docker run --rm -v $(CURDIR):/workdir -w /workdir -it tmp/ulos_env g++ -O0 -Wall --std=c++14 -nostdinc -nostdlib -T mmap.ld crt0.S main.cc
	docker run --rm -v $(CURDIR):/workdir -w /workdir -it --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" tmp/ulos_env strace ./a.out

mem_file:
	dd if=/dev/zero of=./mem_file bs=1024 count=1024

docker:
	docker build --no-cache -t tmp/ulos_env docker