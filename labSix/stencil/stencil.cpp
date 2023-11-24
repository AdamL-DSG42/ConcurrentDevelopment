// stencil.cpp --- 
// 
// Filename: stencil.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Mon Feb  4 10:10:27 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: 24 Nov 2023
//           By: Adam Lambert
//     Update #: 41
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

/*! \mainpage Concurrency Lab Six Stencil
 *
 * \section Description
 *
 * Completed version of Lab Six Stencil.
 *
 * Demonstrates parallelised summing of two separate vectors
 *
 * \section p How to Run
 *
 *  stencil.cpp:
 *
 *  Compiled using g++, run make -k to create
 *
 *  Run ./stencil.out to run the program
 *
 */

// Code:

/*! \file stencil.cpp
    \brief Demonstrates parallelised summing of two separate vectors, similar to the map function but
    also includes the current values neighbours in the concurrent function
*/

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <functional>  /* function type */
#include <limits>
#include <vector>      /* vectors used instead of arrays */

using namespace std ;

//array dimension
const int DIM=1000;
const int SIZE=4;

/*! \fn int calcNeighbours(vector<float> const  &in, int index, vector<float>& out)
    \brief Puts the neighbours of the elements of the first vector into the second vector

    \param in float vector containing the initial values
    \param index integer containing location of initial value
    \param out float vector that stores the neighbours of the element in the in vector
*/
int calcNeighbours(vector<float> const  &in, int index, vector<float>& out){
  int amount=out.size();
  for(int i=0;i<out.size();++i){//put neighbours of in[i] into out vector
    int k=i-amount/2;
    if (k<0){//wrap k around size of in vector
      k=in.size()+k;
    }else if (k>=in.size()){
      k=k-in.size();
    }
    out[i]=in[k];
  }
  return 1;
}

/*! \fn void stencil(vector<float> const &in, vector<float> &out,
	     function <float(vector<float>) > f,int size)
    \brief Sums the neighbour of each element of the first vector and stores the result in the second vector

    \param in float vector containing the initial values
    \param out float vector that stores the sum of the neighbours of the element in the in vector
    \param f stores the getNewValue function
    \param size Dictates the size of the neighbour vector, 4 indicates a Von Nueman neighbourhood
*/
void stencil(vector<float> const &in, vector<float> &out,
	     function <float(vector<float>) > f,int size){
#pragma openmp parallel for
  for (int i=0; i < in.size(); ++i){
    vector<float> neighbours(size);
    calcNeighbours(in,i,neighbours);
    out[i]=f(neighbours);
  }
}



/*! \fn float getNewValue(vector<float> currentValues)
    \brief Sums the vector of neighbours of each element returned in the stencil function

    \param currentValues vector of the element of the initial vector's neighbours
*/
float getNewValue(vector<float> currentValues){
  float average=0.0;
  float total=0.0;
  for(auto const& value: currentValues){
    total+=value;
  }
  return total/currentValues.size();
}

int main(void){
  vector<float> first(DIM), second(DIM);
  //initilise vectors
  srand (time(NULL));
   
  for(auto& value: first) {
    value=(float)rand() / ((float)(RAND_MAX)+(float)(1));
  }
  for(auto it=second.begin(); it<second.end();++it){
    *it=0.0f;
  }
  //
  float sum=0.0f;
  for(auto const&value: first){
    sum+=value;
  }
  cout << sum <<endl;
  stencil(first,second,getNewValue,SIZE);
  sum=0.0f;
  for(auto const&value: second){
    sum+=value;
  }
  cout << sum <<endl;
  return 0;
}
// 
// stencil.cpp ends here
