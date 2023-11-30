# Adam Lambert

CXX = g++
CPPFILES=simulation.cpp
HFILES=tileConstants.h
OBJFILES=simulation.o
CPPFLAGS=-std=c++11 -I. -Wall -fopenmp
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -fopenmp
EXE=watorSimulation

SRCS=simulation.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)  $(DEBUGFLAGS)


ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm $(OBJFILES)
