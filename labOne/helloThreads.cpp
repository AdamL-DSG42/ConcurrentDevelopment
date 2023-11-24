// helloThreads.cpp --- 
// 
// Filename: helloThreads.cpp
// Description: A simple program that prints two messages in the correct order concurrently
// Author: Adam Lambert
// Maintainer: Adam Lambert
// Created: Mon Sep 27 2023
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
#include <thread>
#include <unistd.h>

/*! \file helloThreads.cpp
    \brief An Implementation of basic signalling using Semaphores

    Uses C++11 features such as semaphores to implement a basic concurrent print order

*/

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief Prints the first message to be displayed.

    \param theSemaphore Shared semaphore used to ensure the second message waits for the first message.
    \param delay Dictates how long the first task should sleep before running.
*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();   /**< Signal allows task two to start*/
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief Prints the second message to be displayed.

    \param theSemaphore Shared semaphore used to ensure the second message waits for the first message.
*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();   /**< Task two waits for task one to signal it's start */
  std::cout <<"This ";
  std::cout << "will ";
  sleep(5);
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}


int main(void){
  std::thread threadOne, threadTwo;   /**< Create two threads threadOne and threadTwo */
  std::shared_ptr<Semaphore> sem( new Semaphore);   /**< Create a new semaphore sem */
  int taskOneDelay=5;   /**< Create int taskOneDelay set to 5 */
  threadOne=std::thread(taskTwo,sem);   /**< Launch thread for taskTwo */
  threadTwo=std::thread(taskOne,sem,taskOneDelay);    /**< Launch thread for taskOne */
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish and join them */
  threadOne.join();
  threadTwo.join();
  return 0;
}
