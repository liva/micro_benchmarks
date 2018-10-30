.PHONY: env docker

default:
	diff -uprN linux-4.4.0.orig linux-4.4.0 > change.patch || :
	docker run --rm -it -v $(CURDIR):/workdir tmp/gettsc_source sh -c "patch -p1 < /workdir/change.patch && fakeroot debian/rules -j 32 binary-headers binary-generic binary-perarch && cp ../*.deb /workdir"

env:
	docker build -t tmp/gettsc_source docker
	docker rm -f gettsc_source || :
	docker run -d --rm -it --name gettsc_source tmp/gettsc_source sh
	docker cp gettsc_source:/linux.tar.gz .
	docker rm -f gettsc_source
	tar xf linux.tar.gz
	mv linux-4.4.0 linux-4.4.0.orig
	tar xf linux.tar.gz
	rm -f linux.tar.gz
