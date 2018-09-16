#include "Solver.h"

Solver::Solver(int player_id, int board_size, int time_limit)
{
    //cerr << "Solver got board_size = " << board_size << endl;
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
	string move_str;
	if(current_board->no_my_rings() < 5)
	{
		int a = 4, b = turns;
		turns++;
		Ring* new_ring = new Ring(a, b, 1);

		// current_board->filled_pos[100*a + b] = 1;
		current_board->add_ring(new_ring);
		//cerr << "CERR: Entering score " << endl;
		current_board->score();
		//cerr << "CERR: Exiting score " << endl;
		
		move_str = "P " + to_string(a) + " " + to_string(b) + " \n";
	}
	else
	{
		//cerr<<"alpha_beta"<<endl;
		int counter = 0;
		pair<Ring*, pair<int,int>> move = Solver::alpha_beta(current_board, 0, 2, counter);
		pair<int,int> a = move.first->get_position();
		pair<int,int> b = move.second;
		move_str = "S " + to_string(a.first) + " " + to_string(a.second) + " M " + to_string(b.first) + " " + to_string(b.second)+" \n";

		current_board = generate_board(current_board, move, 0);
	}

	// Block opp move in 1 move: Aakash
	return move_str;
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
pair<Ring*, pair<int,int>> Solver::alpha_beta(Board* temp, int depth, int final_depth, int &counter)
{
	//cerr<<"yo"<<endl;
	vector<pair<Ring*, pair<int,int>>> neighbours = Solver::get_neighbours(temp, depth%2);
	int index = 0;
	int res_score = depth%2 == 0 ? INT_MAX : INT_MIN;
	//cerr<<"here"<<endl;
	for (int i=0; i<neighbours.size();i++)
	{
		// cerr<<"i"<<endl;
		Board* child = generate_board(temp, neighbours[i], depth%2);
		counter++;
		cerr << "Board no " << counter << endl;; 
		if (depth != final_depth)
		{
			pair<Ring*, pair<int,int>> move = alpha_beta(child, depth+1, final_depth, counter);
			Board* new_board = generate_board(child, move, 1-depth%2);
		}
		int score = child->score();
		if(depth%2 == 0 ? score > res_score : score < res_score)
		{
			res_score = score;
			index = i;
		}

		delete child;
	}

	return neighbours[index];
}

vector<pair<Ring*, pair<int,int>>> Solver::get_neighbours(Board* my_board, int polarity)
{
	vector<pair<Ring*, pair<int,int>>> neighbours;
	vector<Ring*> my_rings;
	if (polarity == 0)
		my_rings = my_board->get_my_rings();
	else
		my_rings = my_board->get_opp_rings();

	for (int i=0;i<my_rings.size();i++)
	{
		// cerr<<i<<endl;
		Ring* current_ring = my_rings[i];
		pair<int,int> current_position = current_ring->get_position();
		for(int direction=0; direction<6;direction++)
		{
			//cerr<<direction<<endl;
			vector<pair<int,int>> possible_positions = my_board->get_possible_positions(current_position, direction);
			//cerr<<"problem?"<<endl;//
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

Board* Solver::generate_board(Board* my_board, pair<Ring*, pair<int,int>> neighbour, int polarity)
{
	Board* new_board = new Board(my_board);
	vector<Ring*> rings = new_board->get_my_rings();
	pair<int,int> my_pos = neighbour.first->get_position();

	int index = 0;
	for (int i=0;i<rings.size();i++)
	{
		pair<int,int> pos = rings[i]->get_position();
		if(pos.first == my_pos.first && pos.second == my_pos.second)
			index = i;
	}

	pair<int,int> final_position = rings[index]->get_position();
	Marker* marker = new Marker(my_pos.first, my_pos.second, polarity);
	new_board->add_marker(marker);
	rings[index]->move(final_position.first, final_position.second);

	return new_board;
}

