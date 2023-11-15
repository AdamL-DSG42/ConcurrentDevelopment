#include "fish.h"

/*! \class Fish
    \brief Implementation of Fish

   Details the relevant attributes of the fish class for the Wa-Tor simulation

*/

/*! Fish constructor*/
Fish::Fish(){

  fishPop = 0;
  fishBreed = 0;
  fishAge = 0;

}

/*! Fish with parameter constructor*/
Fish::Fish(int pop, int breed){
  
  fishPop = pop;
  fishBreed = breed;
  fishAge = 0;

}

/*! Fish deconstructor*/
Fish::~Fish(){

}

/*! allows fish to move to a random available space*/
void Fish::move(){

}

/*! allows fish to reproduce after an amount of time specified by fishBreed*/
void Fish::reproduce(){
    
}
