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

https://github.com/AdamL-DSG42/ConcurrentDevelopment/tree/main/labTwo

### Description:

Completed version of Lab Two.
Demonstrates a simple use of semaphores to print two sentences in the correct order. Use Makefile to create this program.
Also demonstrates the use of a simple mutex lock to increment a shared variable consistently. Use MakefileMutualEx to create this program.

### Files:

1. MakeFile - Makefile for the rendezvous.cpp file
2. rendezvous - Executable of rendezvous.cpp
3. rendezvous.cpp - C++11 file demonstrating mutliple threads rendezvousing to print text in the correct order
4. Semaphore.cpp/Semaphore.h - C++11 implementation of Semaphores using features such as mutex locks and conditionals
