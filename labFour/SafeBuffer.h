/* SafeBuffer.h --- 
 * 
 * Filename: SafeBuffer.h
 * Description: 
 * Author: Adam Lambert
 * Maintainer: 
 * Created: Tue Oct 10 2023
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Sun Oct 15 2023
 *           By: Adam Lambert
 *     Update #: 1
 * URL: 
 * Doc URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change Log:
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
#include "Event.h"
#include <stdio.h>
#include <queue>

class SafeBuffer
{
private:

  // create Array - change to queue if possible
  std::queue<std::shared_ptr<Event>> buffer;
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> itemsSem;
  std::shared_ptr<Semaphore> spacesSem;
  std::shared_ptr<int> bufferSize;
  int bufferLimit;

public:

  SafeBuffer();
  ~SafeBuffer();
  SafeBuffer(int size);
  void Get();
  void Put(int i);
  
};

/* SafeBuffer.h ends here */
