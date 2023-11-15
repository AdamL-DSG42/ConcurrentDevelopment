// simulation.cpp --- 
// 
// Filename: simulation.cpp
// Description: Runs a Wa-Tor simulation
// Author: Adam Lambert
// Maintainer: Adam Lambert
// Created: Mon Nov 13 2023
// Last-Updated: Mon Nov 13 2023
//           By: Adam Lambert
//     Update #: 1
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
#include <time.h>

const int gridSize = 40000;
const int xdim = 200; 
const int ydim = 200;
int WindowXSize = 2800;
int WindowYSize = 1700;
int cellXSize = WindowXSize/xdim;
int cellYSize = WindowYSize/ydim;
//each shape will represent either a fish, shark or empty space
//e.g. blue for empty, red for shark and green for fish
sf::RectangleShape recArray[xdim][ydim];
int worldData[xdim][ydim];

void swap (int &a, int &b){ 
    int temp = a; 
    a = b; 
    b = temp; 
} 

void shuffle(int *arr, int rows, int cols){

  srand (time(NULL)); 
  int totalSize = rows * cols;

  for(int i=totalSize-1;i>0;--i){
    int k = rand() % (i+1);
    swap(*(arr + i), *(arr + k));
  }
}

int main(){
  int gridTotal = 0;
  int fishPop = 20;
  int sharkPop = 2;
  int water = 0;
  int fish = 1;
  int shark = 2;

  for(int i=0;i<xdim;++i){
    for(int k=0;k<ydim;++k){
      if(gridTotal < fishPop){
        worldData[i][k] = fish;
      }
      else if(gridTotal < fishPop+sharkPop){
        worldData[i][k] = shark;
      }
      else {
        worldData[i][k] = water;
      }
      gridTotal++;
    }
  }

  int *oneDimArray = &worldData[0][0];
  shuffle(oneDimArray, xdim, ydim);

  for(int i=0;i<xdim;++i){
    for(int k=0;k<ydim;++k){
      recArray[i][k].setSize(sf::Vector2f(cellXSize,cellYSize));
      recArray[i][k].setPosition(i*cellXSize,k*cellYSize);
      if (worldData[i][k] == water) recArray[i][k].setFillColor(sf::Color::Blue);
      else if (worldData[i][k] == fish) recArray[i][k].setFillColor(sf::Color::Green);
      else if (worldData[i][k] == shark) recArray[i][k].setFillColor(sf::Color::Red);
    }
  }

  sf::RenderWindow window(sf::VideoMode(WindowXSize,WindowYSize), "SFML Wa-Tor world");

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }
    //loop these three lines to draw frames
      window.clear(sf::Color::Black);
      for(int i=0;i<xdim;++i){
          for(int k=0;k<ydim;++k){
              window.draw(recArray[i][k]);
          }
      }
      window.display();
  }

  return 0;
}

// 
// simulation.cpp ends here