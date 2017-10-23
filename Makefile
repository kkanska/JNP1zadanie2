CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -O2
CXXFLAGS=-Wall -Wextra -O2 -std=c++17
DEBUG=-DNDEBUG

all: ctests

ctests: dict.o dictglobal.o
	$(CC) -c $(CFLAGS) dict_test1.c -o dict_test1.o
	$(CXX) -c $(CXXFLAGS) dict_test2a.cc -o dict_test2a.o
	$(CXX) -c $(CXXFLAGS) dict_test2b.cc -o dict_test2b.o
	$(CXX) dict_test1.o dict.o dictglobal.o -o dict_test1
	$(CXX) dict_test2a.o dict.o dictglobal.o -o dict_test2a
	$(CXX) dict_test2b.o dict.o dictglobal.o -o dict_test2b

dict.o:
	$(CXX) -c $(CXXFLAGS) dict.cc -o dict.o

dictglobal.o:
	$(CXX) -c $(CXXFLAGS) dictglobal.cc -o dictglobal.o