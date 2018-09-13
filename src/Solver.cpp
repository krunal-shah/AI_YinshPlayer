#include "Solver.h"

Solver::Solver(int player_id, int board_size, int time_limit)
{
    current_board = new Board(board_size);
    turns = 1;
}

Solver::Solver(Solver* base_solver)
{
    turns = base_solver->turns;
    Board* new_board = new Board(base_solver->current_board);
    current_board = new_board;
}


// Add constructor to copy a board : Krunal(Done)
// Given a position and a direction, return possible end positions: Aakash
vector<pair<int, int>> Solver::get_possible_position(pair<int, int> current_position, int direction)
{
	int radius = current_position.first;
	int offset = current_position.second;

	if( direction*radius == offset )
	{
		// lies on axis
		markers = current_board->markers;
		rings = current_board->rings;
	}
	else
	{
		// does not lie on axis
	}
}

pair<int, int> Solver::get_next_position(pair<int, int> current_position, int direction)
{
	int radius = current_position.first;
	int offset = current_position.second;
	pair<int, int> next_position;

	if( direction*radius == offset )
	{
		// lies on axis (same direction)
		next_position.first = radius + 1;
		next_position.second = offset;

	}
	else if ( direction*radius == (offset+3*radius)%(6*radius) )
	{
		//lies on axis (opp direction)
		next_position.first = radius - 1;
		next_position.second = offset;
	}
	else
	{
		// does not lie on axis
		segment = offset/radius;
		if( direction == (segment + 5)%6 )
		{

		}
		else if ( direction == (segment + 2)%6 )
		{
			/* code */
		}
		else if ( direction ==  )
		{
			/* code */
		}
	}
}
// Basic 5 window return moves and scores : Krunal


string Solver::move()
{
	if(current_board->no_my_rings() < 5)
	{
		int a = turns, b = 0;
		turns++;
		Ring* new_ring = new Ring(a, b, 1);

		// current_board->filled_pos[100*a + b] = 1;
		current_board->add_ring(new_ring);
		
		string move_str = "P " + to_string(a) + " " + to_string(b) + " \n";
		return move_str;
	}
	else
	{

	}

	// Block opp move in 1 move: Aakash
	return "P 10 10";
}

void Solver::make_opp_move(string move)
{
	if(move[0] == 'P')
	{
		int a, b;
		int i = 2, j = 2;
		while(move[j] != ' ')
			j++;
		a = stoi(move.substr(i, j - i));
		int n = move.length() - 1;
		string temp_str = move.substr(j, n - j + 1);
		b = stoi(temp_str, nullptr, 10);

		Ring* new_ring = new Ring(a, b, 0);

		// filled_pos[100*a + b] = 0;
		current_board->add_ring(new_ring);
	}
}
