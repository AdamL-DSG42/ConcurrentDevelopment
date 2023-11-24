// mutualEx.cpp --- 
// 
// Filename: mutualEx.cpp
// Description: A simple program that demonstrates the proper updating of a shared variable by multiple threads
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

/*! \mainpage Concurrency Lab One
 *
 * \section Description
 *
 * Completed version of Lab One.
 *
 * Demonstrates a simple use of semaphores to print two sentences in the correct order. 
 *
 * Also demonstrates the use of a simple mutex lock to increment a shared variable consistently.
 *
 * \section p How to Run
 *
 *  helloThreads.cpp:
 *
 *  Compiled using g++, run make -k to create
 *
 *  Run ./helloThreads to run the program
 *
 *  mutualEx.cpp:
 *
 *  Compiled using g++, run make -k -f MakefileMutualEx to create
 *
 *  Run ./mutualEx to run the program
 *
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


static const int num_threads = 100;   /**< Number of threads to be created by the program */
int sharedVariable=0;   /**< Initialise sharedVariable to 0 */
std::mutex mLock;   /**< Create mutex mLock */


/*! \file mutualEx.cpp
    \brief An Implementation of Mutual Exclusion using Semaphores

     Uses C++11 features such as mutex and condition variables to implement an example of a mutex lock for threads

*/
/*! \fn updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief increments a sharedVariable by one numUpdates amount of times across multiple threads

    \param numUpdates Dictates the amount of times the sharedVariable should be incremented
*/
void updateTask(int numUpdates){
  for(int i=0;i<numUpdates;i++){
    mLock.lock();   /**< Use mutex lock to make thread hold sharedVariable */
    sharedVariable++;
    mLock.unlock();   /**< Release mutex lock on sharedVariable */
  }
}


int main(void){
  std::vector<std::thread> vt(num_threads);   /**< Create the amount of threads dictated by num_threads */
  for(std::thread& t: vt){
    t=std::thread(updateTask,1000);   /**< Run updateTask 1000 times */
  }
  std::cout << "Launched from the main\n";
  for (auto& v :vt){
      v.join();   /**< Join the threads with the main thread */
  }
  std::cout << sharedVariable << std::endl;
  sharedVariable = 0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,5);    /**< Run updateTask 5 times */
  }
  for (auto& v :vt){
    v.join();   /**< Join the threads with the main thread */
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
