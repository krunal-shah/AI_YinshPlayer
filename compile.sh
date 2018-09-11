
#!/bin/bash

## Compile our two program files
g++ -std=c++11 -Ofast -march=native -o code ./src/Board.cpp ./src/Marker.cpp ./src/Ring.cpp ./src/Solver.cpp ./src/main.cpp
