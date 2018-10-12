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
    bool start;

public:
    Solver(int, int, int);
    Solver(Solver* base_solver);
    void make_opp_move(string move);
    string move();
    pair<int, vector<int> > alpha_beta(Board* temp, int depth, int final_depth, int &counter, int alpha, int beta);
    vector<pair<pair<int,int>, pair<int,int>>> get_neighbours(Board* my_board, int polarity);
    Board* generate_board(Board* my_board, pair<pair<int,int>, pair<int,int>> neighbour, int polarity);

    Ring* decide_remove_ring(Board* board);
};

#endif  /* SOLVER_H */

