#include "Barrier.h"

/*! \class Barrier
    \brief An Implementation of a barrier Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement a barrier using Semaphores with N number threads

*/
/*! Barrier constructor*/
Barrier::Barrier(){

  taskCount = 0;
  threadNum = 0;
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem1=std::make_shared<Semaphore>(0);
  barrierSem2=std::make_shared<Semaphore>(1);
}
/*! Barrier with parameter constructor*/
Barrier::Barrier(int taskCount){
  
  this->taskCount = taskCount;
  threadNum = 0;
  std::shared_ptr<Semaphore> mutexSem(new Semaphore(1));
  std::shared_ptr<Semaphore> barrierSem1(new Semaphore(0));
  std::shared_ptr<Semaphore> barrierSem2(new Semaphore(1));
}
/*! Barrier deconstructor*/
Barrier::~Barrier(){

}

/*! sets count value*/
void Barrier::setCount(int x){

  this->taskCount = x;
}
/*! returns count value*/
int Barrier::getCount(){

  return this->taskCount;
}

/*! waits for all the threads before starting second half of code*/ 
void Barrier::waitForAll(){

  mutexSem->Wait();
  threadNum++;

  if(threadNum == taskCount){
    barrierSem2->Wait();
    barrierSem1->Signal();
    threadNum = 0;
  }
  mutexSem->Signal();
  barrierSem1->Wait();
  barrierSem1->Signal();

  mutexSem->Wait();
  threadNum++;

  if(threadNum == taskCount){
    barrierSem1->Wait();
    barrierSem2->Signal();
    threadNum = 0;
  }
  mutexSem->Signal();
  barrierSem2->Wait();
  barrierSem2->Signal();
}
