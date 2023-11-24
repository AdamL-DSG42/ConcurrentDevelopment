// quicksort.cpp --- 
// 
// Filename: quicksort.cpp
// Description: 
// Author: Joseph Kehoe
// Maintainer: 
// Created: Sat Feb  9 16:43:33 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: 24 Nov 2023
//           By: Adam Lambert
//     Update #: 104
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

/*! \mainpage Concurrency Lab Six Sort
 *
 * \section Description
 *
 * Completed version of Lab Six Sort.
 *
 * Demonstrates parallelised sorting on a quicksort algorithm
 *
 * \section p How to Run
 *
 *  quicksort.cpp:
 *
 *  Compiled using g++, run make -k to create
 *
 *  Run ./qsort.out to run the program
 *
 */

// Code:

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <functional>  /* function type */
#include <limits>
#include <vector>      /* vectors used instead of arrays */

using namespace std ;

/*! \file quicksort.cpp
    \brief Demonstrates parallelised sorting on a quicksort algorithm
*/

const int LENGTH=2000;

/*! \fn int partition (vector<int>& myArray , int low , int high )
    \brief Partition the supplied vector and return the location of the quicksort pivot point

    \param myArray integer vector to be sorted
    \param low location of first value in the vector
    \param high location of last value in the vector
*/
int partition (vector<int>& myArray , int low , int high ){
  int pivot=myArray[high];
  int k=high;
  int i=low;
  int temp=0;
  while (i<k){
    while (myArray[i]<pivot && i<k)++i;
    while (myArray[k]>pivot && i<k)--k;
    if (i<k){
      temp=myArray[i];
      myArray[i]=myArray[k];
      myArray[k]=temp;
      i++;//do not decrement k here OR ELSE!!
    }
  }
  return i-1;
}
  
/*! \fn int quicksort(vector<int>& myArray , int low , int high )
    \brief Sort the supplied vector from lowest to highest

    \param myArray integer vector to be sorted
    \param low location of first value in the vector
    \param high location of last value in the vector
*/
int quicksort(vector<int>& myArray , int low , int high ){
  if (low<high){
    int pivot=partition(myArray,low,high);
    //really we should only do this if each partition is above a certain size (1000 elements?)
    //otherwise the overhead outweighs any gains from using threads
    #pragma omp task shared(myArray)
    quicksort(myArray,low,pivot);
    quicksort(myArray,pivot+1,high);
    #pragma omp taskwait
  return 1;
  }
}//quicksort



int main(void){
  srand (time(NULL));
  vector<int> data(LENGTH);
  for(auto& value:data){
    value=rand()%1000;
  }
  for(auto& value:data){
    cout<<value<<" ";
  }
  cout << endl<<"*******************************"<<endl;
  quicksort(data,0,data.size()-1);
  for(auto& value:data){
    cout<<value<<" ";
  }
  cout << endl;
}
// 
// quicksort.cpp ends here
