default:
	g++ -O3 --std=c++14 -Wall main.cc
	./a.out

docker:
	docker run -it -v $(CURDIR):/home/jovyan/work --rm -p 8888:8888 jupyter/scipy-notebook
