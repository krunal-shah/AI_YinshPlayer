#include "Solver.h"

Solver::Solver(int player_id, int board_size, int time_limit)
{
    cerr << "Solver got board_size = " << board_size << endl;
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


string Solver::move()
{
	if(current_board->no_my_rings() < 5)
	{
		int a = turns, b = 0;
		turns++;
		Ring* new_ring = new Ring(a, b, 1);

		// current_board->filled_pos[100*a + b] = 1;
		current_board->add_ring(new_ring);
		cerr << "CERR: Entering score " << endl;
		current_board->score();
		cerr << "CERR: Exiting score " << endl;
		
		string move_str = "P " + to_string(a) + " " + to_string(b) + " \n";
		return move_str;
	}
	else
	{
		
	}

	// Block opp move in 1 move: Aakash
	return "P 10 10";
}

void Solver::make_opp_move(string move_str)
{
	vector< pair< string, pair< int, int> > > moves;
	moves = fill_moves(move_str);
	for(int i=0; i < moves.size(); i++)
	{	
		pair< string, pair< int, int> > move = moves[i];
		int a = move.second.first;
		int b = move.second.second;
		string mtype = move.first;
		if(mtype == "P")
		{
			int polarity = 0;
			Ring* new_ring = new Ring(a, b, polarity);

			// filled_pos[100*a + b] = 0;
			current_board->add_ring(new_ring);
		}
		else if(mtype == "S")
		{
			Marker* new_marker = new Marker(a, b, 0);
			current_board->add_marker(new_marker);
			
			int index = get_board_index(a, b);
			pair<char, void*> selected_pair = current_board->get_configuration(index);
			Ring* selected_ring = (Ring*)selected_pair.second;
			
			pair< string, pair< int, int> > next_move = moves[i++];
			int c = next_move.second.first, d = next_move.second.second;
			selected_ring->move(c, d);
			int new_index = get_board_index(c, d);

			selected_pair.second = selected_ring;
			current_board->set_configuration(selected_pair, new_index);
		}
	}
}
