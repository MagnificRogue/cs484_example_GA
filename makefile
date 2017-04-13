SHELL = /bin/bash

CC=g++

OPT_LEVEL = -O0

BASIC_PERF=$(CC) -g -O2  -std=c++11 

all:  geneticAlgorithm.exe 

geneticAlgorithm.exe: main.cpp
	$(BASIC_PERF) -o geneticAlgorithm.exe main.cpp

clean:
	rm *.exe 
