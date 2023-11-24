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

https://github.com/AdamL-DSG42/ConcurrentDevelopment/tree/main/labOne

### Description:

Completed version of Lab One.
Demonstrates a simple use of semaphores to print two sentences in the correct order. Use Makefile to create this program.
Also demonstrates the use of a simple mutex lock to increment a shared variable consistently. Use MakefileMutualEx to create this program.

### Files:

1. helloThreads - Executable of helloThreads.cpp
2. helloThreads.cpp - Simple use of semaphores to ensure that two threads complete their tasks of printing a sentence in the correct order.
3. Makefile - Simple makefile for use with helloThreads.cpp
4. Makefile1/Makefile2/Makefile3 - Sample makefiles provided with lab
5. MakefileMutualEx - Simple makefile for use with mutualEx.cpp
6. mutualEx - Executable of mutualEx.cpp
7. mutualEx.cpp - Simple use of a mutex lock to ensure that multiple threads increment a shared variable the correct amount of times
8. Semaphore.cpp/Semaphore.h - C++11 implementation of semaphores using features such as mutex locks and conditionals
9. Semaphore.o/helloThreads.o/mutualEx.o - Object files of the afformentioned cpp files


