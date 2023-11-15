#include <stdio.h>

/*! \class Fish
    \brief Implementation of Fish

   Details the relevant attributes of the fish class for the Wa-Tor simulation

*/
class Fish
{
private:

  int fishPop;
  int fishBreed;
  int fishAge;

public:

  Fish();
  ~Fish();
  Fish(int pop, int breed);
  void move();
  void reproduce();
};