## README

### Licence:

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
 
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.

### Author:

Adam Lambert

### Git URL:

https://github.com/AdamL-DSG42/ConcurrentDevelopment/tree/main/WaTorProject

### Description:

In Progress version of the Wa-Tor Simulation Project.

Simulates an ecosystem of Fish and Sharks which each have different behaviours

Displays the created ecosystem simulation and how it progresses using SFML

### Files:

1. MakeFile - Makefile for the simulation.cpp file
2. simulation.cpp - C++11 file demonstrating an implementation of the Wa-Tor Simulation as explained [here](https://en.wikipedia.org/wiki/Wa-Tor)
3. simulation.o - Object file of the simulation.cpp file
4. tileConstants.h - Contains constant values implemented by the simulation.cpp file for testing purposes
5. watorSimulation - Executable file for the simulation.cpp file
6. Speed-Up-Test-Results.txt - Text file containing the results of speed-up benchmark tests completed
7. speedUpGraph.py - Python script that generates the speed-up graph from the results of the benchmark test
8. Wa-Tor Speed-up Report.odt - Open Document Format file that contains a report on the findings from the speed-up benchmark tests completed on the concurrent version of the Wa-Tor project