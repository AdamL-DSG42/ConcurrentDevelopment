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
#include "fish.h"
#include "shark.h"
#include "tileConstants.h"

const int gridSize = xdim*ydim;
int cellXSize = WindowXSize/xdim;
int cellYSize = WindowYSize/ydim;
sf::RectangleShape watorArray[xdim][ydim];
GridTile* worldData[xdim][ydim];

// Swap the value of two integers
void swap (int &a, int &b){ 
    int temp = a; 
    a = b; 
    b = temp; 
} 

// Randomly shuffle all of the tiles in the flattened 2D array
void shuffle(int *arr, int rows, int cols){
  int totalSize = rows * cols;

  for(int i = totalSize - 1; i > 0; --i){
    int k = rand() % (i+1);
    swap(*(arr + i), *(arr + k));
  }
}

// Create a vector of all empty neighbours of a tile
void getEmptyNeighbours(int row, int col, std::vector<std::pair<int, int>>& emptyNeighbours){
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
  for (int i = 0; i < emptyNeighbours.size(); i++) {
    // Printing the element at
    // index 'i' of vector
    std::cout << "Empty Neighbour Vector: " << emptyNeighbours[i].first << ", " << emptyNeighbours[i].second << std::endl;
  }
}

// Find a random neighbour of a tile that is a fish
// std::tuple<int, int> getRandomFishNeighbour(int row, int col){
//   std::vector<int> neighbours = getNeighbours(row, col);
//   int randRow = 0;
//   int randCol = 0;
//   if(std::find(neighbours.begin(), neighbours.end(), fish) != neighbours.end()){

//     return {randRow, randCol};
//   }
//   return {-1, -1};
// }

// Move fish to random adjacent tile
void fishMove(int row, int col){
  if (!alreadyMoved){
    std::vector<std::pair<int, int>> emptyNeighbours;
    getEmptyNeighbours(row, col, emptyNeighbours);
    if(emptyNeighbours.size() > 0){
      int randChoice = rand() % emptyNeighbours.size();
      std::pair<int, int> chosenTile = emptyNeighbours[randChoice];
      worldData[row][col] = water;
      std::cout << row << ", " << col << std::endl;
      worldData[chosenTile.first][chosenTile.second] = fish;
      std::cout << chosenTile.first << ", " << chosenTile.second << std::endl;
    }
  }
}

int main(){
  int gridTotal = 0;
  int fishPop = 20;
  int sharkPop = 5;

  // Populate grid with fish, sharks and water tiles
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      if(gridTotal < fishPop){
        worldData[i][k] = new Fish();
      }
      else if(gridTotal < fishPop+sharkPop){
        worldData[i][k] = new Shark();
      }
      else {
        worldData[i][k] = new Water();
      }
      gridTotal++;
    }
  }

  // Flatten the 2D array and shuffle all of the tiles to randomly place fish and sharks
  srand (time(NULL)); 
  GridTile* *oneDimArray = &worldData[0][0];
  shuffle(oneDimArray, xdim, ydim);

  // Set colours of tiles to the appropriate colour based on whether it is a fish, shark or water
  for(int i = 0; i < xdim; ++i){
    for(int k = 0; k < ydim; ++k){
      watorArray[i][k].setSize(sf::Vector2f(cellXSize,cellYSize));
      watorArray[i][k].setPosition(i*cellXSize,k*cellYSize);
      if (worldData[i][k].getType() == water) watorArray[i][k].setFillColor(sf::Color::Blue);
      else if (worldData[i][k].getType() == fish) watorArray[i][k].setFillColor(sf::Color::Green);
      else if (worldData[i][k].getType() == shark) watorArray[i][k].setFillColor(sf::Color::Red);
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

    float chronon = 0.5f;
    if(clock.getElapsedTime().asSeconds() >= chronon) {
      for(int i = 0; i < xdim; ++i){
        for(int k = 0; k < ydim; ++k){
          if(worldData[i][k].getType() == fish){
            fishMove(i, k);
          }
        }
      }
      clock.restart();
    }  

    // Set colours of tiles to the appropriate colour based on whether it is a fish, shark or water
    for(int i = 0; i < xdim; ++i){
      for(int k = 0; k < ydim; ++k){
        if (worldData[i][k].getType() == water) watorArray[i][k].setFillColor(sf::Color::Blue);
        else if (worldData[i][k].getType() == fish) watorArray[i][k].setFillColor(sf::Color::Green);
        else if (worldData[i][k].getType() == shark) watorArray[i][k].setFillColor(sf::Color::Red);
      }
    }

    window.clear(sf::Color::Black);
    for(int i = 0; i < xdim; ++i){
        for(int k = 0; k<ydim; ++k){
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