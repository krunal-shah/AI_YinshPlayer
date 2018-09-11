#include "Solver.h"

Solver::Solver(int player_id, int board_size, int time_limit)
{
    current_board = new Board();
    turns = 0;
}

// Add constructor to copy a board : Krunal
// Given a position and a direction, return possible end positions: Aakash
// Basic 5 window return moves and scores : Krunal


string Solver::move()
{
	// Block opp move in 1 move: Aakash

	// 

	string a = "P " + to_string(turns) + " 0\n";
	turns++;
	return a;
}
