#include "Event.h"
#include "SafeBuffer.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
const int size=20;


/*! \fn producer
    \brief Creates events and adds them to buffer
*/

void producer(std::shared_ptr<SafeBuffer<std::shared_ptr Event>> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
    theBuffer->Put(i);
  }
  
}

/*! \fn consumer
    \brief Takes events from buffer and consumes them
*/

void consumer(std::shared_ptr<SafeBuffer<std::shared_ptr Event>> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    theBuffer->Get();
  }
  
}

int main(void){

  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>> aBuffer( new SafeBuffer<shared_ptr<Event>>(size));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aBuffer,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
