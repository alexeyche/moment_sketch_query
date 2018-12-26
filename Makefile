CC=gcc
CXX=g++

RM=rm -f

CFLAGS=-std=c99
CXXFLAGS=-g -msse2 -O0 -std=c++14 -Iinclude -Ikissfft
LDFLAGS=

CXX_SRCS=src/tests.cpp
CC_SRCS=kissfft/kiss_fft.c
HEADERS=$(wildcard include/*.h)

OBJS=$(subst .cpp,.o,$(CXX_SRCS)) $(subst .c,.o,$(CC_SRCS))

all: tests

tests: $(OBJS) $(HEADERS)
	$(CXX) -o $@ $(OBJS)

tests.o: tests.cpp
	$(CXX) -c $<

kiss_fft.o: kiss_fft.c
	$(CC) -c $<

clean:
	$(RM) $(OBJS) tests
