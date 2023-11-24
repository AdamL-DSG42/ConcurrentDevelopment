// rendezvous.cpp --- 
// 
// Filename: rendezvous.cpp
// Description: A program that creates a rendezvous using mutexs and semaphores, printing the correct words 
// in the correct order
// Author: Adam Lambert
// Maintainer: Adam Lambert
// Created: Mon Sep 29 2023
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

/*! \mainpage Concurrency Lab Two
 *
 * \section Description
 *
 * Completed version of Lab Two.
 *
 * Demonstrates the use of mutexs and semaphores to print the word first the specified amount of times 
 * before printing the word second the specified amount of times.
 *
 * \section p How to Run
 *
 *  rendezvous.cpp:
 *
 *  Compiled using g++, run make -k to create
 *
 *  Run ./rendezvous to run the program
 *
 */

#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! \file rendezvous.cpp
    \brief An Implementation of a Rendezvous using mutexs and semaphores

     Uses C++11 features such as mutex and semaphores to implement an example of a rendezvous for threads

*/
/*! \fn task(std::shared_ptr<int> numArrived, std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount)
    \brief print the word first the specified amount of times before printing second the specified amount of times

    \param numArrived A shared integer that stores the amount of threads that have arrived at the mutex wait
    \param mutexSem A shared semaphore that is used to create a mutex lock rendezvous
    \param barrierSem A shared semaphore that is used to allow the threads to continue when needed
    \param threadCount An integer that stores the total amount of threads
*/
void task(std::shared_ptr<int> numArrived, std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount){
  
  std::cout << "first " << std::endl;

  mutexSem->Wait();   /**< Add mutex lock to incrementation of numArrived to ensure correct incrementation of variable */
  *numArrived = *numArrived + 1;    /**< Increment shared integer numArrived by one */

  if (*numArrived == threadCount) {
    barrierSem->Signal();   /**< Signal barrierSem when the final thread arrives */
  }

  mutexSem->Signal();   /**< Signal mutex when finished using threadCount */
  barrierSem->Wait();   /**< Wait for signal from last thread and immediately signal the next thread  */
  barrierSem->Signal();
  std::cout << "second" << std::endl;
}




int main(void){
  std::shared_ptr<int> numArrived;
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  int threadCount = 5;
  numArrived=std::make_shared<int>(0);    /**< Initialise numArrived as a shared int to 0 */
  mutexSem=std::make_shared<Semaphore>(1);    /**< Initialise mutexSem as a shared semaphore to 1 */
  barrierSem=std::make_shared<Semaphore>(0);    /**< Initialise barrierSem as a shared semaphore to 0 */
  std::vector<std::thread> threadArray(threadCount);    /**< Initialise a vector of threads of size threadCount */

  for(long unsigned int i = 0; i < threadArray.size(); ++i){
    threadArray[i] = std::thread(task,numArrived,mutexSem,barrierSem,threadCount);  /**< Run task 5 times */
  }

  for(long unsigned int i = 0; i < threadArray.size(); ++i){
    threadArray[i].join();  /**< Join the threads with the main thread */
  }
  
  return 0;
}
