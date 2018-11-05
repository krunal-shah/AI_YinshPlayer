#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<fstream>
#include<vector>
#include <cstdlib>
#include "Board.h"
#include "Util.h"
using namespace std;
using namespace std::chrono; 
class Solver {
private:

    Board* current_board;
    int turns;
    bool start;
    int consecutive_markers;
    int board_size;

public:
    Solver(int, int, int, int);
    void make_opp_move(string move);
    string move();
    pair<int, vector<int> > alpha_beta(Board* temp, int depth, int final_depth, int &counter, int alpha, int beta);
    vector<pair<pair<int,int>, pair<int,int>>> get_neighbours(Board* my_board, int polarity);
    pair<Board*,int> generate_board(Board* my_board, pair<pair<int,int>, pair<int,int>> neighbour, int polarity);

    Ring* decide_remove_ring(Board* board, int polarity);
    vector<vector<int>> get_combinations (int max_rings, int num_rings);
};

#endif  /* SOLVER_H */

