# Author: Adam Lambert (C00257510)

CC=g++
CFLAGS=-std=c++11 -pthread -Wall
CPPFILES=helloThreads.cpp Semaphore.cpp
HFILES=Semaphore.h
OBJFILES=helloThreads.o Semaphore.o
EXE=helloThreads

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(OBJFILES) $(HFILES)
	$(CC) -o $(EXE) $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm $(OBJFILES)
