// mandelbroit.cpp --- m
// 
// Filename: mandelbroit.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Mon Feb  4 09:40:41 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Nov 24 2023
//           By: Adam Lambert
//     Update #: 19
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
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

/*! \mainpage Concurrency Lab Six Map
 *
 * \section Description
 *
 *  mandelbroit.cpp:
 *
 *  Calculates values of a Mandelbrot set, returning the time it took to complete the calculations
 *
 *  saxpy.cpp:
 *
 *  Takes as input two vectors of 32-bit floats X and Y with N elements each, and a scalar value A. It multiplies each element X[i] by A and adds the result to Y[i].
 *
 * \section p How to Run
 *
 *  mandelbroit.cpp:
 *
 *  Compiled using g++, run make -k MANDEL to create
 *
 *  Run ./mandelbroit.out to run the program
 *
 *  saxpy.cpp:
 *
 *  Compiled using g++, run make -k SAXPY to create
 *
 *  Run ./saxpy.out to run the program
 *
 */

// Code:

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <limits>

/*! \file mandelbroit.cpp
    \brief Calculates a mandelbroit set and returns the time it took to complete the calculations
*/

using namespace std ;

const int ROW=1000;
const int COL=1000;
const int DEPTH=10;

/*! \fn int calc(complex<int> c, int depth)
    \brief Double complex value z and add complex value c to it until the absolute value of z is greater than 2.0
    returning the count of how many iterations it took for this to occur or for the required depth to be reached

    \param c complex integer of the form (x,y) received from the mandel function
    \param depth Dictates the amount of times z should be calculated and tested before completing
*/
int calc(complex<int> c, int depth){
    int count=0;
    complex<int> z=0;
    for(int i=0;i<depth;++i){
      if (abs(z)>2.0){
                break;
      }
      z=z*z+c;
      count++;
    }
    return count;
}

/*! \fn void mandel(int p[ROW][COL], int depth)
    \brief Using openmp parallel for collapse, parallelise two for loops which call the calc function, 
    storing the returned count in 2D array p

    \param p 2D integer array used to contain the returned count from the calc function
    \param depth Used to supply the depth for the calc function
*/
void mandel( int p[ROW][COL], int depth){
  #pragma omp parallel for collapse(2)	  
  for(int i=0;i<ROW;++i){
        for(int k=0;k<COL;++k){
	  p[i][k]=calc(complex<int>(i,k),depth);
	}
    }
}

int main(void){

  
  int myArray[ROW][COL];
  /* initialize random seed: */
  srand (time(NULL));
  
  clock_t begin = clock();
  mandel(myArray,DEPTH);
  clock_t end = clock();
  double timeSec = (end - begin) / static_cast<double>( CLOCKS_PER_SEC );
  std::cout << timeSec << std::endl;
}


// 
// mandelbroit.cpp ends here
