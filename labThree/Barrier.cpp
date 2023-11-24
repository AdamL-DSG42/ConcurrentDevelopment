// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: An implementaion of a barrier using two shared semaphores
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

#include "Barrier.h"

/*! \file Barrier.cpp
    \brief An Implementation of a barrier using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement a barrier using Semaphores with N number threads

*/
/*! \fn Barrier()
    \brief basic Barrier constructor
*/
Barrier::Barrier(){

  taskCount = 0;
  threadNum = 0;
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem1=std::make_shared<Semaphore>(0);
  barrierSem2=std::make_shared<Semaphore>(1);
}
/*! \fn Barrier(int taskCount)
    \brief Barrier constructor that takes taskCount as parameter

    \param taskCount The total number of threads
*/
Barrier::Barrier(int taskCount){
  
  this->taskCount = taskCount;
  threadNum = 0;
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem1=std::make_shared<Semaphore>(0);
  barrierSem2=std::make_shared<Semaphore>(1);
}
/*! \fn ~Barrier()
    \brief Barrier deconstructor
*/
Barrier::~Barrier(){

}

/*! \fn int getCount()
    \brief Returns taskCount of a Barrier object
*/
int Barrier::getCount(){

  return this->taskCount;
}

/*! \fn waitForAll()
    \brief Implements Barrier that waits for all threads before continuing to execute code
*/
void Barrier::waitForAll(){

  mutexSem->Wait();   /**< Add mutex lock to incrementation of threadNum to ensure correct incrementation of variable */
  threadNum++;

  if(threadNum == taskCount){
    barrierSem2->Wait();
    barrierSem1->Signal();    /**< Signal barrierSem1 and wait barrierSem2 when the final thread arrives */
  }
  mutexSem->Signal();   /**< Signal mutex when finished using threadNum */
  barrierSem1->Wait();    /**< Wait for signal from last thread and immediately signal the next thread */
  barrierSem1->Signal();

  mutexSem->Wait();
  threadNum--;

  if(threadNum == 0){
    barrierSem1->Wait();
    barrierSem2->Signal();    /**< Wait barrierSem1 and signal barrierSem2 when the final thread arrives */
    threadNum = 0;
  }
  mutexSem->Signal();   /**< Signal mutex when finished using threadNum */
  barrierSem2->Wait();    /**< Wait for signal from last thread and immediately signal the next thread */
  barrierSem2->Signal();
}
