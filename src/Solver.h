#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<fstream>
#include<vector>
#include "Board.h"
using namespace std;

class Solver {
private:

    Board* current_board;
    int turns;

public:
    Solver(int, int, int);
    string move();
    
    
};

#endif  /* SOLVER_H */

