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
string Solver:alpha_beta(Board* temp, int depth, int final_depth)
{
	vector<pair<Ring*, pair<int,int>>> neighbours = Solver::get_neighbours(temp);
	int index = 0;
	int res_score = depth%2 == 0 ? INT_MAX : INT_MIN
	for (int i=0; i<neighbours.size();i++)
	{
		Board* child = generate_board(temp, neighbours[i]);
		int score = depth == final_depth ? child->score() : Solver::alpha_beta(child, depth+1, final_depth);
		if(depth%2 == 0 ? score > res_score : score < res_score)
		{
			res_score = score;
			index = i;
		}
	}

	return neighbours[index];
}

vector<pair<Ring*, pair<int,int>>> Solver::get_neighbours(Board* my_board)
{
	vector<pair<Ring*, pair<int,int>>> neighbours;
	vector<Ring*> my_rings = my_board->my_rings;

	for (int i=0;i<my_rings.size();i++)
	{
		Ring* current_ring = my_rings[i];
		pair<int,int> current_position = current_ring->get_position();
		for(int direction=0; direction<6;direction++)
		{
			vector<pair<int,int>> possible_positions = my_board->get_possible_positions(current_position, direction);
			for (int j=0;j<possible_positions.size();j++)
			{
				pair<Ring*, pair<int,int>> elem;
				elem.first = current_ring;
				elem.second = possible_positions[j];
				neighbours.push_back(elem);
			}
		}
	}

	return neighbours;
}

Board* generate_board(Board* my_board, pair<Ring*, pair<int,int>> neighbour)
{
	Board* new_board = new Board(my_board);
	vector<Ring*> rings = new_board->my_rings;
	pair<int,int> my_pos = neighbour.first->get_position;

	int index = 0;
	for (int i=0;i<rings.size();i++)
	{
		pair<int,int> pos = rings[i]->get_position();
		if(pos.first == my_pos && pos.second == my_pos.second)
			index = i;
	}

	pair<int,int> final_position = rings[index]->get_position();
	rings[i]->move(final_position.first, final_position.second);

	return new_board;
}

