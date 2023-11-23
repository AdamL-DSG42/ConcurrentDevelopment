// simulation.cpp --- 
// 
// Filename: simulation.cpp
// Description: Runs a Wa-Tor simulation
// Author: Adam Lambert
// Maintainer: Adam Lambert
// Created: Mon Nov 13 2023
// Last-Updated: Mon Nov 20 2023
//           By: Adam Lambert
//     Update #: 2
// 
// 

//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
//
// Code:

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <ctime>
// #include "fish.h"
// #include "shark.h"
#include "tileConstants.h"

const int gridSize = xdim*ydim;
int cellXSize = WindowXSize/xdim;
int cellYSize = WindowYSize/ydim;

struct Tile {
  bool alreadyMoved = false;
  int breedTime = 0;
  int breedOccur = 0;
  int starveTime = 0;
  int starveDeath = 0;
  int type = water;
  sf::Color creatureColour = sf::Color::Blue;
};

sf::RectangleShape watorArray[xdim][ydim];
Tile worldData[xdim][ydim];

// Swap the value of two integers
void swap (Tile &a, Tile &b){ 
    Tile temp = a; 
    a = b; 
    b = temp; 
} 

// Randomly shuffle all of the tiles in the flattened 2D array
void shuffle(Tile *arr, int rows, int cols){
  int totalSize = rows * cols;

  for(int i = totalSize - 1; i > 0; --i){
    int k = rand() % (i+1);
    swap(*(arr + i), *(arr + k));
  }
}

void moveReset(){
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      worldData[i][k].alreadyMoved = false;
    }
  }
}

// Create a vector of all empty neighbours of a tile
void getFishNeighbours(int row, int col, std::vector<std::pair<int, int>>& fishNeighbours){
  if(worldData[row][(((col + 1) % ydim) + ydim) % ydim].type == fish){
    fishNeighbours.push_back(std::make_pair(row, ((((col + 1) % ydim) + ydim) % ydim)));
  }
  if(worldData[row][(((col - 1) % ydim) + ydim) % ydim].type == fish){
    fishNeighbours.push_back(std::make_pair(row, ((((col - 1) % ydim) + ydim) % ydim)));
  }
  if(worldData[(((row + 1) % xdim) + xdim) % xdim][col].type == fish){
    fishNeighbours.push_back(std::make_pair(((((row + 1) % xdim) + xdim) % xdim), col));
  }
  if(worldData[(((row - 1) % xdim) + xdim) % xdim][col].type == fish){
    fishNeighbours.push_back(std::make_pair(((((row - 1) % xdim) + xdim) % xdim), col));
  }
}

// Create a vector of all empty neighbours of a tile
void getEmptyNeighbours(int row, int col, std::vector<std::pair<int, int>>& emptyNeighbours){
  if(worldData[row][(((col + 1) % ydim) + ydim) % ydim].type == water){
    emptyNeighbours.push_back(std::make_pair(row, ((((col + 1) % ydim) + ydim) % ydim)));
  }
  if(worldData[row][(((col - 1) % ydim) + ydim) % ydim].type == water){
    emptyNeighbours.push_back(std::make_pair(row, ((((col - 1) % ydim) + ydim) % ydim)));
  }
  if(worldData[(((row + 1) % xdim) + xdim) % xdim][col].type == water){
    emptyNeighbours.push_back(std::make_pair(((((row + 1) % xdim) + xdim) % xdim), col));
  }
  if(worldData[(((row - 1) % xdim) + xdim) % xdim][col].type == water){
    emptyNeighbours.push_back(std::make_pair(((((row - 1) % xdim) + xdim) % xdim), col));
  }
}

void fishUpdate(int row, int col){
  std::vector<std::pair<int, int>> emptyNeighbours;
  getEmptyNeighbours(row, col, emptyNeighbours);
  worldData[row][col].breedTime++;
  if(emptyNeighbours.size() > 0){
    Tile moveTile = worldData[row][col];
    int randChoice = rand() % emptyNeighbours.size();
    std::pair<int, int> chosenTile = emptyNeighbours[randChoice];
    worldData[chosenTile.first][chosenTile.second] = moveTile;
    worldData[chosenTile.first][chosenTile.second].alreadyMoved = true;
    if(worldData[row][col].breedTime >= worldData[row][col].breedOccur){
      worldData[row][col].type = fish;
      worldData[row][col].creatureColour = sf::Color::Green;
      worldData[row][col].breedTime = 0;
    }
    else{
      worldData[row][col].type = water;
      worldData[row][col].creatureColour = sf::Color::Blue;
    }
  }
}

void sharkUpdate(int row, int col){
  if(worldData[row][col].starveTime == worldData[row][col].starveDeath){
    worldData[row][col].type = water;
    worldData[row][col].breedTime = 0;
    worldData[row][col].starveTime = 0;
    worldData[row][col].creatureColour = sf::Color::Blue;
  }
  else {
    std::vector<std::pair<int, int>> fishNeighbours;
    getFishNeighbours(row, col, fishNeighbours);
    std::vector<std::pair<int, int>> emptyNeighbours;
    getEmptyNeighbours(row, col, emptyNeighbours);
    worldData[row][col].breedTime++;
    worldData[row][col].starveTime++;
    if(fishNeighbours.size() > 0){
      Tile moveTile = worldData[row][col];
      int randChoice = rand() % fishNeighbours.size();
      std::pair<int, int> chosenTile = fishNeighbours[randChoice];
      worldData[chosenTile.first][chosenTile.second] = moveTile;
      worldData[chosenTile.first][chosenTile.second].starveTime = 0;
      worldData[chosenTile.first][chosenTile.second].alreadyMoved = true;
      if(worldData[chosenTile.first][chosenTile.second].breedTime >= worldData[chosenTile.first][chosenTile.second].breedOccur){
        worldData[row][col].type = shark;
        worldData[row][col].creatureColour = sf::Color::Red;
        worldData[chosenTile.first][chosenTile.second].breedTime = 0;
      }
      else{
        worldData[row][col].type = water;
        worldData[row][col].creatureColour = sf::Color::Blue;
      }
    }
    else if(emptyNeighbours.size() > 0){
      Tile moveTile = worldData[row][col];
      int randChoice = rand() % emptyNeighbours.size();
      std::pair<int, int> chosenTile = emptyNeighbours[randChoice];
      worldData[chosenTile.first][chosenTile.second] = moveTile;
      worldData[chosenTile.first][chosenTile.second].breedTime++;
      worldData[chosenTile.first][chosenTile.second].alreadyMoved = true;
      if(worldData[row][col].breedTime >= worldData[row][col].breedOccur){
        worldData[row][col].type = shark;
        worldData[row][col].creatureColour = sf::Color::Red;
        worldData[chosenTile.first][chosenTile.second].breedTime = 0;      
      }
      else{
        worldData[row][col].type = water;
        worldData[row][col].creatureColour = sf::Color::Blue;
        worldData[chosenTile.first][chosenTile.second].breedTime++;
      }
    }
  }
}

// Move creature to random adjacent tile
void move(int row, int col){
  if (!worldData[row][col].alreadyMoved){
    if(worldData[row][col].type == fish){
      fishUpdate(row, col);
    }
    else if(worldData[row][col].type == shark) {
      sharkUpdate(row, col);
    }
  }
}

int main(){
  //std::cout << ""
  int gridTotal = 0;
  int fishPop = 100;
  int sharkPop = 20;

  // Populate grid with fish, shark and water tiles
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      if(gridTotal < fishPop){
        worldData[i][k].type = fish;
        worldData[i][k].breedOccur = 3;
        worldData[i][k].creatureColour = sf::Color::Green;
      }
      else if(gridTotal < fishPop+sharkPop){
        worldData[i][k].type = shark;
        worldData[i][k].breedOccur = 6;
        worldData[i][k].starveDeath = 5;
        worldData[i][k].creatureColour = sf::Color::Red;
      }
      else {
        worldData[i][k].type = water;
        worldData[i][k].creatureColour = sf::Color::Blue;
      }
      gridTotal++;
    }
  }

  // Flatten the 2D array and shuffle all of the tiles to randomly place fish and sharks
  srand (time(NULL)); 
  Tile *oneDimArray = &worldData[0][0];
  shuffle(oneDimArray, xdim, ydim);

  // Set colours of tiles to the appropriate colour based on whether it is a fish, shark or water
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      watorArray[i][k].setSize(sf::Vector2f(cellXSize,cellYSize));
      watorArray[i][k].setPosition(i*cellXSize,k*cellYSize);
      watorArray[i][k].setFillColor(worldData[i][k].creatureColour);
    }
  }

  sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");
  sf::Clock clock;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    float chronon = 0.1f;
    if(clock.getElapsedTime().asSeconds() >= chronon) {
      for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
          if(worldData[i][k].type != water){
            move(i, k);
          }
        }
      }
      clock.restart();
    }

    moveReset();  

    // Set colours of tiles to the appropriate colour based on whether it is a fish, shark or water
    for(int i = 0; i < xdim; ++i){
      for(int k = 0; k < ydim; ++k){
        watorArray[i][k].setFillColor(worldData[i][k].creatureColour);
      }
    }

    window.clear(sf::Color::Black);
    for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
            window.draw(watorArray[i][k]);
        }
    }

    window.display();
  }

  return 0;
}

// 
// simulation.cpp ends here

/*
  #pragma omp parallel
  updateGrid(); // put task in function
  int thread_id = get_thread_id;
  int thread_count = get_thread_count;

  for (){}
*/