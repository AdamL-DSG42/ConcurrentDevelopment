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
 *  Choose whether to run the graphical display or speed-up benchmark on line 477
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
#include <fstream>
#include <iostream>
#include <string>
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
const int cellXSize = WindowXSize/xdim;
const int cellYSize = WindowYSize/ydim;

/**< Create global variables of testing variables to be used in the simulation */
const int fishPop = testFishPop;
const int sharkPop = testSharkPop;
const int fishBreed = testFishBreed;
const int sharkBreed = testSharkBreed;
const int sharkStarve = testSharkStarve;
const int totalChrononCount = testChrononCount;

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
        worldData[chosenTile.first][chosenTile.second].breedTime++;
      }
    }
    else if(emptyNeighbours.size() > 0){
      Tile moveTile = worldData[row][col];
      int randChoice = rand() % emptyNeighbours.size();
      std::pair<int, int> chosenTile = emptyNeighbours[randChoice];
      worldData[chosenTile.first][chosenTile.second] = moveTile;
      //worldData[chosenTile.first][chosenTile.second].breedTime++;
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

/*! \fn void runGraphicDisplay()
    \brief Function to display the graphical rendition of the Wa-Tor simulation
*/
void runGraphicDisplay(){
  /**< Initially set colours of tiles to the appropriate colour based on whether it is a fish, shark or water */
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      watorArray[i][k].setSize(sf::Vector2f(cellXSize,cellYSize));
      watorArray[i][k].setPosition(i*cellXSize,k*cellYSize);
      watorArray[i][k].setFillColor(worldData[i][k].creatureColour);
    }
  }

  sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");

  int chrononCount = 0;
  int fishCount = 0;
  int sharkCount = 0;
  while (chrononCount < totalChrononCount)
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    /**< Parallelise the updating of the grid tiles  */
    int threadCount = num_threads;
    #pragma omp parallel num_threads(num_threads) 
    {
      int gridSize = (ydim/threadCount);
      int threadID = omp_get_thread_num();
      int start = threadID * gridSize;
      int end = start + gridSize;
      if(threadID == threadCount - 1){end = ydim;}
      for(int i = start+1; i < end; ++i){
        for(int k = 0; k < xdim; ++k){
          updateTile(k,i);
        }
      }
      /**< Wait for every thread to reach this point before completing the rows shared by each tile */
      #pragma omp barrier
      for(int i = 0; i < xdim; ++i){
        updateTile(i,start);
      }
    }

    moveReset();  

    for(int i = 0; i < xdim; ++i){
      for(int k = 0; k < ydim; ++k){
        if(worldData[i][k].type == 1){
          fishCount++;
        }
        else if(worldData[i][k].type == 2){
          sharkCount++;
        }
      }
    }
    printf("Fish Count: %d\n", fishCount);
    printf("Shark Count: %d\n", sharkCount);
    fishCount = 0;
    sharkCount = 0;

    /**< Reset colours of tiles to the appropriate colour based on new occupant */
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

    chrononCount++;
  }
}

/*! \fn void runSpeedupBenchmark()
    \brief Function to run a speed-up benchmark of the Wa-Tor simulation without a graphical display
*/
void runSpeedupBenchmark(){
  int chrononCount = 0;
  int fishCount = 0;
  int sharkCount = 0;
  double startTime = omp_get_wtime();
  while (chrononCount < totalChrononCount)
  {
    /**< Parallelise the updating of the grid tiles  */
    int threadCount = num_threads;
    #pragma omp parallel num_threads(num_threads) 
    {
      int gridSize = (ydim/threadCount);
      int threadID = omp_get_thread_num();
      int start = threadID * gridSize;
      int end = start + gridSize;
      if(threadID == threadCount - 1){end = ydim;}
      for(int i = start+1; i < end; ++i){
        for(int k = 0; k < xdim; ++k){
          updateTile(k,i);
        }
      }
      /**< Wait for every thread to reach this point before completing the rows shared by each tile */
      #pragma omp barrier
      for(int i = 0; i < xdim; ++i){
        updateTile(i,start);
      }
    }

    moveReset();  

    for(int i = 0; i < xdim; ++i){
      for(int k = 0; k < ydim; ++k){
        if(worldData[i][k].type == 1){
          fishCount++;
        }
        else if(worldData[i][k].type == 2){
          sharkCount++;
        }
      }
    }
    printf("Fish Count: %d\n", fishCount);
    printf("Shark Count: %d\n", sharkCount);
    fishCount = 0;
    sharkCount = 0;

    chrononCount++;
  }

  double endTime = omp_get_wtime();

  printf("Total Execution Time: %f seconds\n",endTime-startTime);

  /**< Write the results of each speed-up test to a text file */
  std::ofstream of;

  of.open("Speed-Up-Test-Results.txt", std::ios::app);
  if (!of)
    std::cout << "File not found";
  else {
    std::string results = "Chronon amount: " + std::to_string(totalChrononCount) + "; Thread Count: " + std::to_string(num_threads) + "; Execution Time: " + std::to_string(endTime-startTime) + " seconds\n\n";
    of << results;
    std::cout << "Data successfully added.\n";
    of.close();
  }
}

int main(){

  int gridTotal = 0;

  /**< Populate grid with fish, shark and water tiles */
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      if(gridTotal < fishPop){
        worldData[i][k].type = fish;
        worldData[i][k].breedOccur = fishBreed;
        worldData[i][k].creatureColour = sf::Color::Green;
      }
      else if(gridTotal < fishPop+sharkPop){
        worldData[i][k].type = shark;
        worldData[i][k].breedOccur = sharkBreed;
        worldData[i][k].starveDeath = sharkStarve;
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
  srand (1000); 
  Tile *oneDimArray = &worldData[0][0];
  shuffle(oneDimArray, xdim, ydim);

  /**< Call functions to either display graphical rendition of Wa-Tor simulation or run speed-up benchmark */
  //runGraphicDisplay();
  runSpeedupBenchmark();

  return 0;
}

// 
// simulation.cpp ends here