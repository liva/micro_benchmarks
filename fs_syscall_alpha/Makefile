define docker_wrapper
	docker run --rm -v ${PWD}:/workdir -w /workdir $1 $2
endef

default:

run:
	$(call docker_wrapper,frolvlad/alpine-gxx,g++ -std=c++14 -Wall main.cc)
	$(call docker_wrapper,frolvlad/alpine-gxx,dd bs=1024 count=1  if=/dev/urandom of='./tmp')
	$(call docker_wrapper,frolvlad/alpine-gxx,./a.out)
	rm -f tmp

clean:
	rm -f a.out tmp