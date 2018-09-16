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
		
		current_board->add_ring(new_ring);
		
		move_str = "P " + to_string(a) + " " + to_string(b) + " \n";
	}
	else
	{
		int counter = 0;
		current_board->print_board();
		pair< int, vector<int> > move = Solver::alpha_beta(current_board, 0, 2, counter);
		
		pair<int,int> a = make_pair(move.second[0], move.second[1]);
		pair<int,int> b = make_pair(move.second[2], move.second[3]);
		int ring_pos = get_board_index(a);
		Ring* ring = (Ring*)current_board->get_configuration(ring_pos).second;
		
		current_board->move_ring(ring, b);
		move_str = "S " + to_string(a.first) + " " + to_string(a.second) + " M " + to_string(b.first) + " " + to_string(b.second)+" \n";

		vector<Ring*> rings = current_board->get_my_rings();

		cerr << "Our move is " << move_str << endl;
 		for (int i=0;i<rings.size();i++)
		{
			pair<int,int> pos = rings[i]->get_position();
			cerr<<pos.first<<" "<<pos.second<<endl;
		}
	}

	// Block opp move in 1 move: Aakash
	return move_str;
}

void Solver::make_opp_move(string move_str)
{
	vector< pair< string, pair< int, int> > > moves;
	moves = fill_moves(move_str);

	// for(int i=0; i<moves.size(); i++)
	// {
	// 	cerr << moves[i].first << " " << moves[i].second.first << " " << moves[i].second.second << endl;
	// }

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
			int index = get_board_index(a, b);
			pair<char, void*> selected_pair = current_board->get_configuration(index);
			Ring* selected_ring = (Ring*)selected_pair.second;
			
			pair< string, pair< int, int> > next_move = moves[++i];
			int c = next_move.second.first, d = next_move.second.second;
			current_board->move_ring(selected_ring, c, d);
		}
	}

	current_board->print_board();
}

pair<int, vector<int> > Solver::alpha_beta(Board* temp, int depth, int final_depth, int &counter)
{
	// cerr<<"yo"<<endl;
	if(depth == final_depth)
	{
		int score = temp->score();
		vector<int> ret(4);
		pair<int, vector<int>> ans;
		ans.first = score;
		ans.second = ret;
		return ans;
	}
	cerr << "Entering get_neighbours" << endl;
	vector<pair<pair<int,int>, pair<int,int>>> neighbours = Solver::get_neighbours(temp, (1+depth)%2);
	cerr << "Exiting get_neighbours" << endl;
	int index = 0;
	int res_score = depth%2 == 0 ? INT_MIN : INT_MAX;
	cerr<<"here"<<endl;
	for (int i=0; i<neighbours.size();i++)
	{
		cerr<<i<<endl;
		Board* child = generate_board(temp, neighbours[i], (1+depth)%2);
		counter++;
		cerr << "Board no " << counter << endl;; 
		
		pair<int, vector<int> > move = alpha_beta(child, depth+1, final_depth, counter);

		int score = move.first;
		
		if(depth%2 == 0)
		{
			if(score > res_score)
			{
				res_score = score;
				index = i;
			}
		}
		else
		{
			if(score < res_score)
			{
				res_score = score;
				index = i;
			}	
		}

		delete child;
	}

	vector<int> ret_vec(4);
	ret_vec[0] = neighbours[index].first.first;
	ret_vec[1] = neighbours[index].first.second;
	ret_vec[2] = neighbours[index].second.first;
	ret_vec[3] = neighbours[index].second.second;
	pair< int, vector<int> > to_return;
	to_return.first = res_score;
	to_return.second = ret_vec;
	return to_return;
}

vector<pair<pair<int,int>, pair<int,int>>> Solver::get_neighbours(Board* my_board, int polarity)
{
	vector<pair<pair<int,int>, pair<int,int>>> neighbours;
	vector<Ring*> my_rings;
	if (polarity == 1)
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
				pair<pair<int,int>, pair<int,int>> elem;
				elem.first = current_position;
				elem.second = possible_positions[j];
				neighbours.push_back(elem);
			}
		}
	}

	cerr << "Printing neighbours" << endl;
	for(int i=0; i<neighbours.size(); i++)
	{
		cerr << neighbours[i].first.first << " " << neighbours[i].first.second << " " << neighbours[i].second.first << " " << neighbours[i].second.second << endl;
	}

	return neighbours;
}

Board* Solver::generate_board(Board* my_board, pair<pair<int,int>, pair<int,int>> neighbour, int polarity)
{
	Board* new_board = new Board(my_board);
	cerr << "Printing new board" << endl;
	new_board->print_board();

	pair<int, int> ring_pos = neighbour.first;
	int	index = get_board_index(ring_pos);
	cerr << "Index = " << index << " ring_pos " << ring_pos.first << " " << ring_pos.second << " " << polarity << endl;

	pair<char, void*> whoa = new_board->get_configuration(index);
	cerr << "ehy" << whoa.first << endl;
	whoa = my_board->get_configuration(index);
	cerr << "ehy" << whoa.first << endl;
	Ring* ring = (Ring*)new_board->get_configuration(index).second;

	pair<int,int> final_position = neighbour.second;
	new_board->move_ring(ring, final_position.first, final_position.second);
	
	return new_board;
}

