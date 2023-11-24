// main.cpp --- 
// 
// Filename: main.cpp
// Description: A program that demonstrates the use of a barrier by printing the word first 5 times then the word second 5 times
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

/*! \mainpage Concurrency Lab Three
*
* \section Description
*
* Completed version of Lab Three.
*
* Demonstrates the use of a barrier to print the word first the specified amount of times 
* before printing the word second the specified amount of times in an array using a barrier.
*
* \section p How to Run
*
*  main.cpp:
*
*  Compiled using g++, run make -k to create
*
*  Run ./barrier to run the program
*
*/

// Code:

#include "Barrier.h"
#include <thread>
#include <vector>

/*! \fn task(std::shared_ptr<Barrier> barrierObj)
    \brief print the word first the specified amount of times before printing second the specified amount of times

    \param barrierObj a barrier object as created in the main
*/
void task(std::shared_ptr<Barrier> barrierObj){
  for(int i = 0; i < 5; ++i){
    std::cout << "first " << std::endl;
    barrierObj->waitForAll();
    std::cout << "second" << std::endl;
    barrierObj->waitForAll();
  }
}

int main(void){

  std::vector<std::thread> threadArray(5);    /**< Initialise a vector of threads of size 5 */
  std::shared_ptr<Barrier> barrierObj(new Barrier(5));    /**< Initialise a shared pointer of type Barrier with a taskCount of 5 */

  for(long unsigned int i=0; i < threadArray.size(); ++i){
    threadArray[i]=std::thread(task,barrierObj);    /**< Run task 5 times in an array*/
  }

  for(long unsigned int i = 0; i < threadArray.size(); ++i){
    threadArray[i].join();    /**< Join the threads with the main thread */
  }
  
  return 0;
}
