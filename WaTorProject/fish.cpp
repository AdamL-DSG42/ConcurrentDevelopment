#include "fish.h"
#include "tileConstants.h"
#include <algorithm>

/*! \class Fish
    \brief Implementation of Fish

   Details the relevant attributes of the fish class for the Wa-Tor simulation

*/

/*! Fish constructor*/
Fish::Fish(){

  row = 0;
  col = 0;
  type = 1;
  fishBreed = 0;
  fishAge = 0;

}

/*! Fish with parameter constructor*/
Fish::Fish(int x, int y, int breed){
  row = x;
  col = y;
  type = 1;
  fishBreed = breed;
  fishAge = 0;

}

/*! Fish deconstructor*/
Fish::~Fish(){

}

/*! allows fish to move to a random available space*/
void Fish::move(int *worldData){
  if (!alreadyMoved){
    std::vector<std::pair<int, int>> emptyNeighbours;
    getEmptyNeighbours(worldData, emptyNeighbours);
    if(emptyNeighbours.size() > 0){
      int randChoice = rand() % emptyNeighbours.size();
      std::pair<int, int> chosenTile = emptyNeighbours[randChoice];
      row = chosenTile.first;
      col = chosenTile.second;
    }
    alreadyMoved = true;
  }
}

void Fish::getEmptyNeighbours(int *worldData, std::vector<std::pair<int, int>>& emptyNeighbours){
  if(worldData[row][(col + 1) % ydim] == water){
    emptyNeighbours.push_back(std::make_pair(row, ((col + 1) % ydim)));
  }
  if(worldData[row][(col - 1) % ydim] == water){
    emptyNeighbours.push_back(std::make_pair(row, ((col - 1) % ydim)));
  }
  if(worldData[(row + 1) % xdim][col] == water){
    emptyNeighbours.push_back(std::make_pair(((row + 1)) % xdim, col));
  }
  if(worldData[(row - 1) % xdim][col] == water){
    emptyNeighbours.push_back(std::make_pair(((row - 1)) % xdim, col));
  }
}

/*! allows fish to reproduce after an amount of time specified by fishBreed*/
void Fish::reproduce(){
    
}

int Fish::getType() const {
  return type;
}
