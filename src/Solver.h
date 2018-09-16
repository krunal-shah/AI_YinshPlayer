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
    pair<Ring*, pair<int,int>> alpha_beta(Board* temp, int depth, int final_depth);
    vector<pair<Ring*, pair<int,int>>> get_neighbours(Board* my_board);
    Board* generate_board(Board* my_board, pair<Ring*, pair<int,int>> neighbour);
};

#endif  /* SOLVER_H */

