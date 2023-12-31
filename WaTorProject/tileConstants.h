// tileConstants.h --- 
// 
// Filename: tileConstants.h
// Description: Contains all constant variables used by simulation.cpp
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

/*! \file tileConstants.h
    \brief Contains constant values used for testing purposes in the simulation.cpp file
*/

#pragma once

/**< Define the size of the wa-tor grid and the window size */

const int xdim = 1000; 
const int ydim = 1000;
const int WindowXSize = 1600;
const int WindowYSize = 1400;


/**< Define the values associated with each tile on the wa-tor grid */
const int water = 0;
const int fish = 1;
const int shark = 2;

/**< Define values used for speed-up benchmark testing */
const int testFishPop = 30000;
const int testSharkPop = 3000;
const int testFishBreed = 3;
const int testSharkBreed = 10;
const int testSharkStarve = 4;
const int testChrononCount = 500;
const int num_threads = 16;