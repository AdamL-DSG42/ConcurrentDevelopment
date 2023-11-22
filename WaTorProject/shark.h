#include "gridTile.h"

/*! \class Shark
    \brief Implementation of Shark

   Details the relevant attributes of the shark class for the Wa-Tor simulation

*/
class Shark : public GridTile
{
private:

  int sharkBreed;
  int sharkAge;
  int sharkEnergy;
  int starveTime;

public:

  Shark();
  ~Shark();
  Shark(int breed, int energy, int starve);
  void move();
  void reproduce();
  void starve();
  int getType() const override;
};