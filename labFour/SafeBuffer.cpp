/* SafeBuffer.cpp --- 
 * 
 * Filename: SafeBuffer.cpp
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

#include "SafeBuffer.h"

SafeBuffer::SafeBuffer(){

  bufferLimit = 0;

}

SafeBuffer::~SafeBuffer(){

}

SafeBuffer::SafeBuffer(int size){

  bufferLimit = size;
  *bufferSize = 0;
  
}

void SafeBuffer::Get(){

  itemsSem->Wait();
  mutexSem->Wait();
  std::shared_ptr<Event> e= buffer.pop();
  --*bufferSize;
  mutexSem->Signal();
  spacesSem->Signal();
  e->Consume();

}

void SafeBuffer::Put(int i){

  if (*bufferSize < bufferLimit) {
    std::shared_ptr<Event> e= std::make_shared<Event>(i);
    spacesSem->Wait();
    mutexSem->Wait();
    buffer.push(e);
    ++bufferSize;
    mutexSem->Signal();
    itemsSem->Signal();
  }
}

/* SafeBuffer.cpp ends here */
