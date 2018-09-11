#include "Solver.h"

Solver::Solver(int player_id, int board_size, int time_limit)
{
    current_board = new Board();
    turns = 0;
}

string Solver::move()
{
	string a = "P " + to_string(turns) + " 0\n";
	turns++;
	return a;
}
