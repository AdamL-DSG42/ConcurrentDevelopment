#ifndef gridTile_h
#define gridTile_h

/*! \class GridTile
    \brief Implementation of GridTile

   Details the relevant attributes of the gridTile class for the Wa-Tor simulation

*/
class GridTile
{
protected:

  int row;
  int col;
  int type;
  bool alreadyMoved;

public:

  virtual void move(int* worldData) = 0;
  void resetMoved(){
    alreadyMoved = false;
  }
  virtual int getType() const = 0;
};

#endif