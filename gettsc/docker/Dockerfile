FROM ubuntu:16.04
RUN su -c "grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list"
RUN apt update -y
RUN apt build-dep -y linux
RUN apt install -y dpkg-dev fakeroot pigz
RUN apt source linux
RUN tar -I pigz -cf linux.tar.gz linux-4.4.0
WORKDIR linux-4.4.0
RUN sh -c "cat debian.master/config/amd64/config.common.amd64 debian.master/config/amd64/config.flavour.generic debian.master/config/config.common.ubuntu > .config"
RUN scripts/config --disable DEBUG_INFO
RUN make -j32 bzImage modules