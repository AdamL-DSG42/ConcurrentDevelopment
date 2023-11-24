# Adam Lambert (C00257510)
# Makefile for lab two rendezvous

CC=g++
CFLAGS=-std=c++11 -pthread -Wall
CPPFILES=rendezvous.cpp Semaphore.cpp
HFILES=Semaphore.h
OBJFILES=rendezvous.o Semaphore.o
EXE=rendezvous

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: $(OBJFILES) $(HFILES)
	$(CC) -o $(EXE) $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm $(OBJFILES)
