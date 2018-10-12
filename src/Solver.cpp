#include "Solver.h"

Solver::Solver(int player_id, int board_size, int time_limit)
{
    //cerr << "Solver got board_size = " << board_size << endl;
    current_board = new Board(board_size);
    turns = 1;
    start = true;
    srand(1234);
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
	if(current_board->no_my_rings() < 5 && start)
	{
		int a = 0, b = 0;
		a = rand()%5;
		if(a != 0)
			b = rand()%(a*6);
		turns++;
		pair<int,int> temp_pos = make_pair(a,b);
		int temp_index = get_board_index(temp_pos);
		while(current_board->get_configuration(temp_index).first != 'n')
		{
			b = 0;
			a = rand()%5;
			if(a!=0)
				b = rand()%(a*6);
			pair<int,int> temp_pos = make_pair(a,b);
			temp_index = get_board_index(temp_pos);
		}
		Ring* new_ring = new Ring(a, b, 1);
		
		current_board->add_ring(new_ring);
		
		move_str = "P " + to_string(a) + " " + to_string(b) + " \n";

		if(current_board->no_my_rings() == 5)
			start = false;
	}
	else
	{
		move_str = "";
		vector<int> to_remove_markers = current_board->detect_success(1);
		// cerr << "Successfully out of success " << to_remove_markers.size() << endl;
		while(to_remove_markers.size() > 0)
		{
			move_str += " RS " + to_string(to_remove_markers[0]) + " " + to_string(to_remove_markers[1]) + " RE " + to_string(to_remove_markers[2]) + " " + to_string(to_remove_markers[3]);
			// cerr << "Move before remove_markers: " << move_str;
			pair<int, int> one_end = make_pair(to_remove_markers[0], to_remove_markers[1]);
			pair<int, int> second_end = make_pair(to_remove_markers[2], to_remove_markers[3]);
			// cerr << "going into remove_markers" << endl;
			current_board->remove_markers(one_end, second_end, 1);
			// cerr << "coming out of remove_markers" << endl;

			Ring* ring_to_remove = decide_remove_ring(current_board,1);
			// cerr << "going into remove_markers" << endl;
			current_board->remove_ring(ring_to_remove);
			// cerr << "coming out of remove_markers" << endl;
			pair<int, int> pos_ring_to_remove = ring_to_remove->get_position();

			move_str += " X " + to_string(pos_ring_to_remove.first) + " " + to_string(pos_ring_to_remove.second);

			// cerr << "Move: " << move_str;

			to_remove_markers = current_board->detect_success(1);
		}


		if(current_board->no_my_rings() <= 2)
		{
			// cerr << "Move: " << move_str;
			move_str = move_str + "\n";

			// cerr << "After our move " << move_str << endl;
			// current_board->print_board();

			return move_str;
		}

		int counter = 0;
		// cerr << "Before our move" << endl;
		// current_board->print_board();
		pair< int, vector<int> > move = Solver::alpha_beta(current_board, 0, 4, counter, INT_MIN, INT_MAX);
		
		pair<int,int> a = make_pair(move.second[0], move.second[1]);
		pair<int,int> b = make_pair(move.second[2], move.second[3]);
		int ring_pos = get_board_index(a);
		Ring* ring = (Ring*)current_board->get_configuration(ring_pos).second;
		
		current_board->move_ring(ring, b);
		move_str = move_str + " S " + to_string(a.first) + " " + to_string(a.second) + " M " + to_string(b.first) + " " + to_string(b.second);

		
		to_remove_markers = current_board->detect_success(1);
		// cerr << "Successfully out of success " << to_remove_markers.size() << endl;
		int i = 4;
		while(to_remove_markers.size() > 0)
		{
			// cerr << "Successfully in success" << endl;
			move_str += " RS " + to_string(to_remove_markers[0]) + " " + to_string(to_remove_markers[1]) + " RE " + to_string(to_remove_markers[2]) + " " + to_string(to_remove_markers[3]);
			// cerr << "Move before remove_markers: " << move_str;
			pair<int, int> one_end = make_pair(to_remove_markers[0], to_remove_markers[1]);
			pair<int, int> second_end = make_pair(to_remove_markers[2], to_remove_markers[3]);
			// cerr << "going into remove_markers" << endl;
			current_board->remove_markers(one_end, second_end, 1);
			// cerr << "coming out of remove_markers" << endl;

			cerr << "Trying to remove ring at " << move.second[i] << endl;
			cerr << "Total rings " << current_board->no_my_rings() << endl;
			Ring* ring_to_remove = current_board->get_my_rings()->at(move.second[i]-(i-4));
			current_board->remove_ring(ring_to_remove);
			pair<int, int> pos_ring_to_remove = ring_to_remove->get_position();

			move_str += " X " + to_string(pos_ring_to_remove.first) + " " + to_string(pos_ring_to_remove.second);

			// cerr << "going into remove_markers" << endl;
			// cerr << "coming out of remove_markers" << endl;

			// cerr << "Move: " << move_str;

			to_remove_markers = current_board->detect_success(1);

			if(current_board->no_my_rings() <= 2)
			{
				// cerr << "Move: " << move_str;
				move_str = move_str + "\n";

				// cerr << "After our move " << move_str << endl;
				// current_board->print_board();

				return move_str;
			}

			i++;
		}
		// cerr << "Move: " << move_str;
		move_str = move_str + "\n";

		// cerr << "After our move " << move_str << endl;
		// current_board->print_board();

		// cerr << "Our move is " << move_str << endl;
 		// for (int i=0;i<rings.size();i++)
		// {
		// 	pair<int,int> pos = rings[i]->get_position();
		// 	cerr<<pos.first<<" "<<pos.second<<endl;
		// }
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
		else if(mtype == "RS")
		{
			int index = get_board_index(a, b);
			pair<char, void*> selected_pair = current_board->get_configuration(index);
			Marker* first_marker = (Marker*)selected_pair.second;

			index = get_board_index(moves[++i].second);
			selected_pair = current_board->get_configuration(index);
			Marker* last_marker = (Marker*)selected_pair.second;

			current_board -> remove_markers(first_marker, last_marker);

			index = get_board_index(moves[++i].second);
			selected_pair = current_board->get_configuration(index);
			Ring* selected_ring = (Ring*)selected_pair.second;		
			
			current_board -> remove_ring(selected_ring);

		}
	}

	// current_board->print_board();
}

vector<vector<int>> Solver::get_combinations (int max_rings, int num_rings)
{
	vector<vector<int>> comb;

	
	if (num_rings == 1)
	{
		for (int i=0;i<max_rings;i++)
		{
			vector<int> temp_vec;
			temp_vec.push_back(i);
			comb.push_back(temp_vec);
		}
	}
	else if (num_rings == 2)
	{
		for (int i=0;i<max_rings;i++)
		{
			for (int j=i+1;j<max_rings;j++)
			{
				vector<int> temp_vec;
				temp_vec.push_back(i);
				temp_vec.push_back(j);
				comb.push_back(temp_vec);
			}
		}
	}
	else
	{
		for (int i=0;i<max_rings;i++)
		{
			for (int j=i+1;j<max_rings;j++)
			{
				for (int k=j+1;k<max_rings;k++)
				{
					vector<int> temp_vec;
					temp_vec.push_back(i);
					temp_vec.push_back(j);
					temp_vec.push_back(k);
					comb.push_back(temp_vec);
				}
			}
		}
	}
	return comb;
}

pair<int, vector<int> > Solver::alpha_beta(Board* temp, int depth, int final_depth, int &counter, int alpha, int beta)
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
	// cerr << "Entering get_neighbours" << endl;
	vector<pair<pair<int,int>, pair<int,int>>> neighbours = Solver::get_neighbours(temp, (1+depth)%2);
	int polarity = (1+depth)%2;

	// vector<pair<pair<int, int>, Board*>> neighbour_boards(neighbours.size());

	// for (int i = 0; i < neighbours.size(); ++i)
	// {
	// 	Board* child = generate_board(temp, neighbours[i], (1+depth)%2);
	// 	int child_score = child->score();
	// 	neighbour_boards[i] = make_pair(make_pair(child_score, i), child);
	// }

	// sort(neighbour_boards.rbegin(), neighbour_boards.rend());

	// cerr << "Sorted scores" << endl;
	// for (int i = 0; i < neighbour_boards.size(); ++i)
	// {
	// 	cerr << i << ". " << neighbour_boards[i].first.first << endl;
	// }

	// cerr << "Exiting get_neighbours" << endl;
	int index = 0;
	int index_ring_removal = -1;
	int res_score = depth%2 == 0 ? INT_MIN : INT_MAX;
	vector<vector<int>> final_combinations;
	// cerr<<"here"<<endl;
	for (int i=0; i<neighbours.size();i++)
	{
		// cerr<<i<<endl;
		pair<Board*,int> child_pair = generate_board(temp, neighbours[i], (1+depth)%2);
		Board* child = child_pair.first;
		int success = child_pair.second;
		success = min(3,success);
		// cerr << "Success is " << success;
		
		if (success)
		{
			// cerr << "In success" << endl;
			int num_rings = polarity ? child->no_my_rings():child->no_opp_rings();
			vector<vector<int>> combinations = get_combinations(num_rings, success);

			for (int j=0; j<combinations.size();j++)
			{
				// cerr << "Trying " << j << " out of " << combinations.size() << endl;
 				//remove ring from temp
				Board* temp = new Board(child);
				vector<int> rings = combinations[j];
				for (int k=0;k<rings.size();k++)
				{
					// cerr << "Removing ring at " << k << endl;
					// cerr << "Total rings " << num_rings << endl;
					if (depth%2 == 0)
					{
						temp->remove_ring(temp->get_my_rings()->at(rings[k]-k));
					}
					else
					{
						temp->remove_ring(temp->get_opp_rings()->at(rings[k]-k));
					}
				}
				// cerr << "Removed ring " << endl;
				pair<int, vector<int> > move = alpha_beta(temp, depth+1, final_depth, counter, alpha, beta);

				int score = move.first;

				if(depth%2 == 0)
				{
					if(score > res_score)
					{
						res_score = score;
						index_ring_removal = j;
						index = i;
						final_combinations = combinations;
					}
				}
				else
				{
					if(score < res_score)
					{
						res_score = score;
						index_ring_removal = j;
						index = i;
						final_combinations = combinations;
					}	
				}
			}
			// cerr << "Out of success" << endl;
		}
		else
		{
			// cerr << "In not success" << endl;
			pair<int, vector<int> > move = alpha_beta(child, depth+1, final_depth, counter, alpha, beta);
			int score = move.first;
			
			if(depth%2 == 0)
			{
				alpha = max(alpha, score);
				if(score > res_score)
				{
					res_score = score;
					index = i;
					index_ring_removal = -1;
				}
			}
			else
			{
				beta = min(beta, score);
				if(score < res_score)
				{
					res_score = score;
					index = i;
					index_ring_removal = -1;
				}	
			}

			delete child;

			if(alpha >= beta)
			{
				// cerr << "yaay pruned" << endl;
				break;
			}
		}
	}
	// cerr<<"here?"<<endl;
	vector<int> ret_vec(4);
	if(index_ring_removal != -1)
	{
		// cerr << "Here \n";
		ret_vec.resize(4+final_combinations[index_ring_removal].size());
		ret_vec[0] = neighbours[index].first.first;
		ret_vec[1] = neighbours[index].first.second;
		ret_vec[2] = neighbours[index].second.first;
		ret_vec[3] = neighbours[index].second.second;
		
		if(depth == 0)
		{	
			cerr << "Printing final combination at " << index_ring_removal << endl;
			for (int i = 0; i < final_combinations[index_ring_removal].size(); ++i)
			{
				cerr << final_combinations[index_ring_removal][i] << " ";
			}
			cerr << endl;
		}

		for (int i = 0; i < final_combinations[index_ring_removal].size(); ++i)
		{
			ret_vec[i+4] = final_combinations[index_ring_removal][i];
		}
		// cerr << "Out of here\n";
	}
	else
	{
		ret_vec[0] = neighbours[index].first.first;
		ret_vec[1] = neighbours[index].first.second;
		ret_vec[2] = neighbours[index].second.first;
		ret_vec[3] = neighbours[index].second.second;
	}
	// cerr << "HERE" << endl;
	pair< int, vector<int> > to_return;
	to_return.first = res_score;
	to_return.second = ret_vec;
	return to_return;
}

vector<pair<pair<int,int>, pair<int,int>>> Solver::get_neighbours(Board* my_board, int polarity)
{
	vector<pair<pair<int,int>, pair<int,int>>> neighbours;
	vector<Ring*>* my_rings;
	if (polarity == 1)
		my_rings = my_board->get_my_rings();
	else
		my_rings = my_board->get_opp_rings();

	// cerr<<"size "<<my_rings.size()<<endl;

	for (int i=0;i<my_rings->size();i++)
	{
		Ring* current_ring = my_rings->at(i);
		pair<int,int> current_position = current_ring->get_position();
		// cerr<<"Finding neighbours for ring " << i << " which is at position " << current_position.first << " " << current_position.second <<endl;
		for(int direction=0; direction<6;direction++)
		{
			//cerr<<direction<<endl;
			vector<pair<int,int>> possible_positions = my_board->get_possible_positions(current_position, direction);
			// cerr<<"size "<<possible_positions.size()<<endl;
			//cerr<<"problem?"<<endl;//
			for (int j=0;j<possible_positions.size();j++)
			{
				// cerr << "Possible positio " << possible_positions[j].first << " " << possible_positions[j].second << endl;
				pair<pair<int,int>, pair<int,int>> elem;
				elem.first = current_position;
				elem.second = possible_positions[j];
				neighbours.push_back(elem);
			}
			// cerr<<"size "<<neighbours.size()<<endl;
		}
	}

	// cerr << "Printing neighbours" << endl;
	// for(int i=0; i<neighbours.size(); i++)
	// {
	// 	cerr << neighbours[i].first.first << " " << neighbours[i].first.second << " " << neighbours[i].second.first << " " << neighbours[i].second.second << endl;
	// }

	return neighbours;
}

pair<Board*,int> Solver::generate_board(Board* my_board, pair<pair<int,int>, pair<int,int>> neighbour, int polarity)
{
	Board* new_board = new Board(my_board);
	// cerr << "Printing new board" << endl;
	// new_board->print_board();

	pair<int, int> ring_pos = neighbour.first;
	int	index = get_board_index(ring_pos);
	// cerr << "Index = " << index << " ring_pos " << ring_pos.first << " " << ring_pos.second << " " << polarity << endl;

	pair<char, void*> whoa = new_board->get_configuration(index);
	// cerr << "ehy" << whoa.first << endl;
	// whoa = my_board->get_configuration(index);
	// cerr << "ehy" << whoa.first << endl;
	Ring* ring = (Ring*)new_board->get_configuration(index).second;

	pair<int,int> final_position = neighbour.second;
	new_board->move_ring(ring, final_position.first, final_position.second);

	// cerr << "Trying to generate board\n";
	vector<int> to_remove_markers = new_board->detect_success(polarity);
	// cerr << "Successfully out of success " << to_remove_markers.size() << endl;
	int success = 0;
	while(to_remove_markers.size() > 0)
	{
		// cerr << "Removing markers\n";
		success++;
		// cerr << "Move before remove_markers: " << move_str;
		pair<int, int> one_end = make_pair(to_remove_markers[0], to_remove_markers[1]);
		pair<int, int> second_end = make_pair(to_remove_markers[2], to_remove_markers[3]);
		// cerr << "going into remove_markers" << endl;
		new_board->remove_markers(one_end, second_end, polarity);
		// cerr << "Removed markers\n";
		// cerr << "coming out of remove_markers" << endl;

		to_remove_markers = new_board->detect_success(polarity);
	}

	// cerr << "Generated board\n";
	pair<Board*,int> ret;
	ret.first = new_board;
	ret.second = success;
	return ret;
}

Ring* Solver::decide_remove_ring(Board* board, int polarity)
{
	if(polarity == 0)
	{
		return (*board->get_opp_rings())[0];	
	}
	return (*board->get_my_rings())[0];
}

