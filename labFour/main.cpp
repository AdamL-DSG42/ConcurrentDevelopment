#include "Event.h"
#include "SafeBuffer.h"
#include <iostream>
#include <thread>
#include <vector>

/*! \mainpage Concurrency Lab Four
 *
 * \section Description
 *
 * Completed version of Lab Five.
 *
 * Demonstrates a solution to the Producer-Consumer problem
 *
 * Does not currently compile
 *
 * \section p How to Run
 *
 *  main.cpp:
 *
 *  Compiled using g++, run make -k to create (does not currently work)
 *
 *  Run ./safeBuffer to run the program
 *
 */


static const int num_threads = 100;
const int size=20;


/*! \fn producer
    \brief Creates events and adds them to buffer
*/

void producer(std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    theBuffer->Put(i);
  }
  
}

/*! \fn consumer
    \brief Takes events from buffer and consumes them
*/

void consumer(std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    theBuffer->Get();
  }
  
}

int main(void){

  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>> aBuffer( new SafeBuffer<std::shared_ptr<Event>>(size));
  /**< Launch the threads  */
  int i=0;
  while(i < 20){
    vt[i] = std::thread(producer,aBuffer,10);
    ++i;
  }
  while(i < num_threads){
    vt[i] = std::thread(consumer,aBuffer,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  return 0;
}
