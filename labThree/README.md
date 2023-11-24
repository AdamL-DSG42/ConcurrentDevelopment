## README

### Licence:

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
 
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.

### Author:

Adam Lambert

### Git URL:

https://github.com/AdamL-DSG42/ConcurrentDevelopment/tree/main/labThree

### Description:

Completed version of Lab Three.

Demonstrates the use of a barrier to print the word first the specified amount of times 
before printing the word second the specified amount of times in an array using a barrier.

### Files:

1. MakeFile - Makefile for the main.cpp file
2. barrier - Executable of main.cpp
3. barrier.cpp - C++11 file creating a Barrier class
4. barrier.h - Header file for barrier.cpp
5. barrier.o - Barrier object file
6. main.cpp - C++11 file demonstrating mutliple threads printing text in the correct order in an array using a barrier
7. main.o - main object file
8. Semaphore.cpp/Semaphore.h/Semaphore.o - C++11 implementation of Semaphores using features such as mutex locks and conditionals
