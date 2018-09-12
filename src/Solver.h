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
    Solver(Solver* base_solver);
    void make_opp_move(string move);
    string move();  
};

#endif  /* SOLVER_H */

