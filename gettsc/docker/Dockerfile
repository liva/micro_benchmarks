FROM ubuntu:16.04
RUN su -c "grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list"
RUN apt update -y
RUN apt build-dep -y linux
RUN apt install -y dpkg-dev fakeroot pigz
RUN apt source linux
RUN tar -I pigz -cf linux.tar.gz linux-4.4.0
WORKDIR linux-4.4.0
RUN cp debian.master/config/amd64/config.flavour.generic .config
RUN make -j32 bindeb-pkg