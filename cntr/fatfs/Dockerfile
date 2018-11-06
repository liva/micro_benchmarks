FROM centos:6
RUN yum update -y
RUN mkdir /sub
RUN yum -y --installroot=/sub --releasever=6 install gdb
RUN tar -cvf fs.tar sub