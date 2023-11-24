// simulation.cpp --- 
// 
// Filename: simulation.cpp
// Description: Runs a Wa-Tor simulation
// Author: Adam Lambert
// Maintainer: Adam Lambert
// Created: Mon Nov 13 2023
// Last-Updated: Mon Nov 24 2023
//           By: Adam Lambert
//     Update #: 5
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

/*! \mainpage Wa-Tor Simulation Project
 *
 * \section Description
 *
 * In progress Wa-Tor Simulation
 *
 * Simulates an ecosystem of Fish and Sharks which each have different behaviours
 *
 * Displays the created ecosystem simulation and how it progresses using SFML
 *
 * \section p How to Run
 *
 *  simulation.cpp:
 *
 *  Compiled using g++, run make -k to create
 *
 *  Run ./watorSimulation to run the program
 *
 */

//
// Code:

/*! \file simulation.cpp
    \brief Simulation of an ecosystem of Fish and Sharks which each have different behaviours, displayed with SFML
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <ctime>
#include <omp.h>
#include "tileConstants.h"

/**< Create global variables of the simulation grids' size and each cells' size */
const int gridSize = xdim*ydim;
int cellXSize = WindowXSize/xdim;
int cellYSize = WindowYSize/ydim;

/*! \struct Tile
    \brief Struct containing the required attributes of each grid tile, updated to contain fish, shark or 
    water as required
*/
struct Tile {
  bool alreadyMoved = false;
  int breedTime = 0;
  int breedOccur = 0;
  int starveTime = 0;
  int starveDeath = 0;
  int type = water;
  sf::Color creatureColour = sf::Color::Blue;
};

/**< Create global variables of the 2D worldData array that contains each Tile and the 2D watorArray array
      that contains the visual representation of each of these tiles */
sf::RectangleShape watorArray[xdim][ydim];
Tile worldData[xdim][ydim];

/*! \fn void swap(Tile &a, Tile &b)
    \brief Function to swap the contents of two Tiles

    \param a First Tile to be swapped
    \param b Second Tile to be swapped
*/
void swap (Tile &a, Tile &b){ 
    Tile temp = a; 
    a = b; 
    b = temp; 
} 

/*! \fn void shuffle(Tile *arr, int rows, int cols)
    \brief Function to shuffle all of the Tiles stored in the flattened worldData array

    \param arr Flattened 2D worldData array
    \param rows Number of rows in the 2D worldData array
    \param cols Number of cols in the 2D worldData array
*/
void shuffle(Tile *arr, int rows, int cols){
  int totalSize = rows * cols;

  for(int i = totalSize - 1; i > 0; --i){
    int k = rand() % (i+1);
    swap(*(arr + i), *(arr + k));
  }
}

/*! \fn void moveReset()
    \brief Function to resetthe move status of all Tiles in the worldData array
*/
void moveReset(){
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      worldData[i][k].alreadyMoved = false;
    }
  }
}

/*! \fn void getFishNeighbours(int row, int col, std::vector<std::pair<int, int>>& fishNeighbours)
    \brief Function to find all of the neighbour Tiles of a current Tile that are of type fish
    using a Von Neuman neighbourhood (North, South, East, West)

    \param row Row position of the current Tile
    \param col Column position of the current Tile
    \param fishNeighbours A vector of pairs of coordinates of each neighbour of a Tile that are of type fish
*/
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

/*! \fn void getEmptyNeighbours(int row, int col, std::vector<std::pair<int, int>>& emptyNeighbours)
    \brief Function to find all of the neighbour Tiles of a current Tile that are of type water
    using a Von Neuman neighbourhood (North, South, East, West)

    \param row Row position of the current Tile
    \param col Column position of the current Tile
    \param emptyNeighbours A vector of pairs of coordinates of each neighbour of a Tile that are of type water
*/
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

/*! \fn void fishUpdate(int row, int col)
    \brief Function to update the state of a fish Tile for every chronon that passes

    \param row Row position of the current Tile
    \param col Column position of the current Tile
*/
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

/*! \fn void sharkUpdate(int row, int col)
    \brief Function to update the state of a shark Tile for every chronon that passes

    \param row Row position of the current Tile
    \param col Column position of the current Tile
*/
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

/*! \fn void updateTile(int row, int col)
    \brief Function to update the state of a Tile based on the type of Tile 

    \param row Row position of the current Tile
    \param col Column position of the current Tile
*/
void updateTile(int row, int col){
  if (!worldData[row][col].alreadyMoved){
    if(worldData[row][col].type == fish){
      fishUpdate(row, col);
    }
    else if(worldData[row][col].type == shark) {
      sharkUpdate(row, col);
    }
  }
}

/*! \fn void updateGrid(sf::Clock clock)
    \brief Function to update the worldData grid each chronon and update the visual simulation based on the
    changes that occur
*/
void updateGrid(sf::Clock clock){
  if(clock.getElapsedTime().asSeconds() >= chronon) {
    for(int i = 0; i < xdim; ++i){
      for(int k = 0; k < ydim; ++k){
        if(worldData[i][k].type != water){
          updateTile(i, k);
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
}

int main(){
  int gridTotal = 0;
  int fishPop = 3000;
  int sharkPop = 300;

  /**< Populate grid with fish, shark and water tiles */
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      if(gridTotal < fishPop){
        worldData[i][k].type = fish;
        worldData[i][k].breedOccur = 3;
        worldData[i][k].creatureColour = sf::Color::Green;
      }
      else if(gridTotal < fishPop+sharkPop){
        worldData[i][k].type = shark;
        worldData[i][k].breedOccur = 10;
        worldData[i][k].starveDeath = 3;
        worldData[i][k].creatureColour = sf::Color::Red;
      }
      else {
        worldData[i][k].type = water;
        worldData[i][k].creatureColour = sf::Color::Blue;
      }
      gridTotal++;
    }
  }

  /**< Flatten the 2D array and shuffle all of the tiles to randomly place fish and sharks */
  srand (time(NULL)); 
  Tile *oneDimArray = &worldData[0][0];
  shuffle(oneDimArray, xdim, ydim);

  /**< Set colours of tiles to the appropriate colour based on whether it is a fish, shark or water */
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

    //updateGrid();

    if(clock.getElapsedTime().asSeconds() >= chronon) {
      for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
          if(worldData[i][k].type != water){
            updateTile(i, k);
          }
        }
      }
      clock.restart();
    }

    moveReset();  

    /**< Set colours of tiles to the appropriate colour based on whether it is a fish, shark or water */
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
  Parallelisation to be implemented

  updateGrid(); // put task in function
  1. Get thread count: int thread_count = get_thread_count;
  2. Size of each grid: rows / total thread count, may not go evenly, give remainder to last grid
  int thread_id = get_thread_id;

  #pragma omp parallel
  {
    int threadCount = omp_get_thread_count();
    int gridSize = row/threadCount;
    int start = threadID * threadRowCount;
    if(threadID == threadCount - 1){end = rowCount};
    int end = start + threadRowCount;
    for(int i = start; i < end; ++i) {
      for(int k = 0; k < cols; ++k) {
        updateGrid();
      }
    }

    to deal with locks, three for loops, each one shares locks.
    Lock adjacent tiles.
  }
*/