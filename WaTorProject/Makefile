# Adam Lambert

CXX = g++
CPPFILES=shark.cpp fish.cpp simulation.cpp
HFILES=shark.h fish.h
OBJFILES=shark.o fish.o simulation.o
CPPFLAGS=-std=c++11 -I. -Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lgomp
EXE=watorSimulation

SRCS=shark.cpp fish.cpp simulation.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

#This rule says that each .o file depends on a .cpp file of the same name
#This is actually built into Make but anyways...
%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)  $(DEBUGFLAGS)


ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm $(OBJFILES)
