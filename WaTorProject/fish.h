#include "gridTile.h"
#include <vector>

/*! \class Fish
    \brief Implementation of Fish

   Details the relevant attributes of the fish class for the Wa-Tor simulation

*/
class Fish : public GridTile
{
private:

  int fishBreed;
  int fishAge;

public:

  Fish();
  ~Fish();
  Fish(int x, int y, int breed);
  void move(int* worldData) override;
  void reproduce();
  void getEmptyNeighbours(int* worldData, std::vector<std::pair<int, int>>& emptyNeighbours);
  int getType() const override;
};