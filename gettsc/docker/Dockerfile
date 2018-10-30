FROM ubuntu:16.04
RUN su -c "grep '^deb ' /etc/apt/sources.list | sed 's/^deb/deb-src/g' > /etc/apt/sources.list.d/deb-src.list"
RUN apt update -y
RUN apt build-dep -y linux
RUN apt install -y dpkg-dev fakeroot
RUN apt source linux
RUN tar -Jcf linux.tar.xz linux-4.4.0
WORKDIR linux-4.4.0
RUN chmod a+x debian/rules
RUN chmod a+x debian/scripts/*
RUN chmod a+x debian/scripts/misc/*
RUN fakeroot debian/rules clean
RUN fakeroot debian/rules -j 8 binary-headers binary-generic binary-perarch
