//Adam Lambert (C00257510)

#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<int> numArrived, std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount){
  
  std::cout << "first " << std::endl;

  //Add mutex lock to incrementation of numArrived to ensure correct incrementation of   variable
  mutexSem->Wait();
  *numArrived = *numArrived + 1;
  mutexSem->Signal();

  //Signal when the last thread arrives at this if statement
  if (*numArrived == threadCount) {
    barrierSem->Signal();
  }
  //Wait for signal from last thread and immediately signal the next thread 
  barrierSem->Wait();
  barrierSem->Signal();
  std::cout << "second" << std::endl;
}




int main(void){
  std::shared_ptr<int> numArrived;
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  int threadCount = 5;
  numArrived=std::make_shared<int>(0);
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
  /*!< An array of threads*/
  std::vector<std::thread> threadArray(threadCount);
  /*!< Pointer to barrier object*/

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,numArrived,mutexSem,barrierSem,threadCount);
  }

  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
