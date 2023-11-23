# Adam Lambert

CXX = g++
CPPFILES=gridTile.cpp simulation.cpp
HFILES=gridTile.h tileConstants.h
OBJFILES=gridTile.o simulation.o
CPPFLAGS=-std=c++11 -I. -Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lgomp
EXE=watorSimulation

SRCS=gridTile.cpp simulation.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)  $(DEBUGFLAGS)


ALL: $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) $(LDFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm $(OBJFILES)
