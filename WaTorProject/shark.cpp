#include "shark.h"

/*! \class Shark
    \brief Implementation of Shark

   Details the relevant attributes of the shark class for the Wa-Tor simulation

*/

/*! Shark constructor*/
Shark::Shark(){

  type = 2;
  sharkBreed = 0;
  sharkAge = 0;
  sharkEnergy = 0;
  starveTime = 0;

}

/*! Shark with parameter constructor*/
Shark::Shark(int breed, int energy, int starve){
  
  type = 2;
  sharkBreed = breed;
  sharkAge = 0;
  sharkEnergy = energy;
  starveTime = starve;

}

/*! Shark deconstructor*/
Shark::~Shark(){

}

/*! allows shark to move to a random available space, priotising eating a nearby fish*/
void Shark::move(){

}

/*! allows shark to reproduce after an amount of time specified by sharkBreed*/
void Shark::reproduce(){
    
}

/*! causes shark to starve if it has not eaten a fish after an amount of time specified by starveTime*/
void Shark::starve(){

}

int Shark::getType() const {
  return type;
}
 