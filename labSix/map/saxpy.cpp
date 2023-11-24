// saxpy.cpp --- 
// 
// Filename: saxpy.cpp
// Description: 
// Author: Joseph Kehoe
// Maintainer: 
// Created: Fri Feb  1 10:12:18 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Nov 24 2023
//           By: Adam Lambert
//     Update #: 26
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

// Code:
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <limits>
#include <omp.h>

/*! \file saxpy.cpp
    \brief Completes saxpy calculations as described in the README and returns the time taken to complete
    the calculations 
*/

/*! \fn void saxpy(unsigned long n, float a,float y[], float x[])
    \brief Add all values of float array y to float a multiplied by the elements of float array x n times

    \param n unsigned long that dictates the amount of times the for loop should be run
    \param a float that is multiplied by the elements of the float array x
    \param y float array that is added to the result of float a multiplied by the elements of the float array x
    \param x float array that is multiplied by float a
*/
void saxpy(unsigned long n, float a,float y[], float x[])
{
#pragma omp parallel for
	for (unsigned long i=0; i < n; ++i)
	{
		y[i]=a * x[i] + y[i];
	}
}

int main(void)
{
  const unsigned long size=1000000;
  const float A=1.234;
  
  float y[size];
  float x[size];
  /* initialize random seed: */
  srand (time(NULL));
  


  for(unsigned long long int i=0;i<size;++i){
    y[i]=i*i;
    /* generate secret number between 1 and 1000000: */
    x[i] = rand() % 1000000 + 1;
  }
  clock_t begin = clock();
  saxpy(size,A,y,x);
  clock_t end = clock();
  double timeSec = (end - begin) / static_cast<double>( CLOCKS_PER_SEC );
  std::cout << timeSec << std::endl;
}

// 
// saxpy.cpp ends here
