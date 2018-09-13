#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<fstream>
#include<vector>
#include "Board.h"
#include "Util.h"
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

    pair<int, int> get_next_position(pair<int, int> current_position, int direction);
    vector<pair<int, int>> get_possible_position(pair<int, int> current_position, int direction);
};

#endif  /* SOLVER_H */

