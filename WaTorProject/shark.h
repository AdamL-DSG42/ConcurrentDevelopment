#include <stdio.h>

/*! \class Shark
    \brief Implementation of Shark

   Details the relevant attributes of the shark class for the Wa-Tor simulation

*/
class Shark
{
private:

  int sharkPop;
  int sharkBreed;
  int sharkAge;
  int sharkEnergy;
  int starveTime;

public:

  Shark();
  ~Shark();
  Shark(int pop, int breed, int energy, int starve);
  void move();
  void reproduce();
  void starve();
};