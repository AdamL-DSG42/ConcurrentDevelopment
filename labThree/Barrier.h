// Barrier.h --- 
// 
// Filename: Barrier.h
// Description: A header file that contains the variables and functions of Barrier.cpp
// Author: Adam Lambert
// Maintainer: Adam Lambert
// Created: Mon Oct 02 2023
// Last-Updated: Mon Nov 24 2023
//           By: Adam Lambert
//     Update #: 2
// 
// 

//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
//
// Code:

#include "Semaphore.h"
#include <iostream>
#include <stdio.h>

/*! \class Barrier
    \brief A Barrier Implementation

    Uses C++11 features such as mutex and condition variables to implement a Barrier class using Semaphores

*/
class Barrier
{
private:

  int taskCount;
  int threadNum;
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem1;
  std::shared_ptr<Semaphore> barrierSem2;


public:

  Barrier();
  ~Barrier();
  Barrier(int count);
  int getCount();
  void waitForAll();
};
