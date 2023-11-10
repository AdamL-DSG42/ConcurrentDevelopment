/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Adam Lambert
 * Maintainer: 
 * Created: Tue Oct 17
 * Last-Updated: Wed Oct 17
 *           By: Adam Lambert
 *     Update #: 13
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Code: */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>

const int COUNT = 5;
const int THINKTIME=3;
const int EATTIME=5;
std::shared_ptr<Semaphore> footman;
std::vector<Semaphore> forks(COUNT);


void think(int myID){
  int seconds=rand() % THINKTIME + 1;
  std::cout << myID << " is thinking! " << std::endl;
  sleep(seconds);
}

void get_forks(int philID){
  footman->Wait();
  forks[philID].Wait();
  forks[(philID+1)%COUNT].Wait();
  std::cout << philID << " holds forks! " << std::endl;
}

void put_forks(int philID){
  forks[philID].Signal();
  forks[(philID+1)%COUNT].Signal();
  std::cout << philID << " releases forks! " << std::endl;
  footman->Signal();
}

void eat(int myID){
  int seconds=rand() % EATTIME + 1;
  std::cout << myID << " is chomping! " << std::endl;
  sleep(seconds);  
}

void philosopher(int id){
  while(true){
    think(id);
    get_forks(id);
    eat(id);
    put_forks(id);
  }//while  
}//philosopher



int main(void){
  srand (time(nullptr)); // initialize random seed: 
  std::vector<std::thread> vt(COUNT);
  for (int i = 0; i < COUNT; ++i){
    forks[i].Signal();
  }
  footman = std::make_shared<Semaphore>(COUNT - 1);
  int id=0;
  for(std::thread& t: vt){
    t=std::thread(philosopher,id++);
  }
  /**< Join the philosopher threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  return 0;
}

/* main.c ends here */
