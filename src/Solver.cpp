#include "Solver.h"

Solver::Solver(int player_id, int bsize, int time_limit, int cmarkers)
{
    current_board = new Board(bsize, cmarkers);
    turns = 1;
    start = true;
    srand(1234);
    board_size = bsize;
    consecutive_markers = cmarkers;
}


// Add constructor to copy a board : Krunal(Done)
// Given a position and a direction, return possible end positions: Aakash

string Solver::move()
{
	string move_str;
	if(current_board->no_my_rings() < board_size && start)
	{
		int a = 0, b = 0;
		a = rand()%board_size;
		if(a != 0)
			b = rand()%(a*6);
		turns++;
		pair<int,int> temp_pos = make_pair(a,b);
		int temp_index = get_board_index(temp_pos);
		while(current_board->get_configuration(temp_index).first != 'n')
		{
			b = 0;
			a = rand()%board_size;
			if(a!=0)
				b = rand()%(a*6);
			pair<int,int> temp_pos = make_pair(a,b);
			temp_index = get_board_index(temp_pos);
		}
		Ring* new_ring = new Ring(a, b, 1);
		
		current_board->add_ring(new_ring);
		
		move_str = "P " + to_string(a) + " " + to_string(b) + " \n";

		if(current_board->no_my_rings() == board_size)
			start = false;
	}
	else
	{
		move_str = "";
		vector<int> to_remove_markers = current_board->detect_success(1);
		while(to_remove_markers.size() > 0)
		{
			move_str += " RS " + to_string(to_remove_markers[0]) + " " + to_string(to_remove_markers[1]) + " RE " + to_string(to_remove_markers[2]) + " " + to_string(to_remove_markers[3]);
			
			pair<int, int> one_end = make_pair(to_remove_markers[0], to_remove_markers[1]);
			pair<int, int> second_end = make_pair(to_remove_markers[2], to_remove_markers[3]);
			
			current_board->remove_markers(one_end, second_end, 1);
			
			Ring* ring_to_remove = decide_remove_ring(current_board,1);
			current_board->remove_ring(ring_to_remove);
			pair<int, int> pos_ring_to_remove = ring_to_remove->get_position();

			move_str += " X " + to_string(pos_ring_to_remove.first) + " " + to_string(pos_ring_to_remove.second);

			to_remove_markers = current_board->detect_success(1);
		}


		if(current_board->no_my_rings() <= 2)
		{
			move_str = move_str + "\n";
			return move_str;
		}

		int counter = 0;
		
		pair< int, vector<int> > move = Solver::alpha_beta(current_board, 0, 3, counter, INT_MIN, INT_MAX);
		
		pair<int,int> a = make_pair(move.second[0], move.second[1]);
		pair<int,int> b = make_pair(move.second[2], move.second[3]);
		// cerr << "a = " << a.first << " " << a.second << endl;
		// cerr << "b = " << b.first << " " << b.second << endl;
		int ring_pos = get_board_index(a);
		Ring* ring = (Ring*)current_board->get_configuration(ring_pos).second;
		
		current_board->move_ring(ring, b);
		move_str = move_str + " S " + to_string(a.first) + " " + to_string(a.second) + " M " + to_string(b.first) + " " + to_string(b.second);
		// cerr << move_str << endl;
		
		to_remove_markers = current_board->detect_success(1);
		int i = 4;
		while(to_remove_markers.size() > 0)
		{
			move_str += " RS " + to_string(to_remove_markers[0]) + " " + to_string(to_remove_markers[1]) + " RE " + to_string(to_remove_markers[2]) + " " + to_string(to_remove_markers[3]);
			
			pair<int, int> one_end = make_pair(to_remove_markers[0], to_remove_markers[1]);
			pair<int, int> second_end = make_pair(to_remove_markers[2], to_remove_markers[3]);
			
			current_board->remove_markers(one_end, second_end, 1);
			
			// cerr << move_str << endl;
			// cerr << "Trying to remove ring at " << move.second[i] << endl;
			// cerr << "Total rings " << current_board->no_my_rings() << endl;
			Ring* ring_to_remove = current_board->get_my_rings()->at(move.second[i]-(i-4));
			current_board->remove_ring(ring_to_remove);
			pair<int, int> pos_ring_to_remove = ring_to_remove->get_position();

			move_str += " X " + to_string(pos_ring_to_remove.first) + " " + to_string(pos_ring_to_remove.second);

			to_remove_markers = current_board->detect_success(1);

			if(current_board->no_my_rings() <= 2)
			{
				move_str = move_str + "\n";
				return move_str;
			}

			i++;
		}
		move_str = move_str + "\n";
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
}

vector<vector<int>> Solver::get_combinations(int max_rings, int num_rings)
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
	int res_score = depth%2 == 0 ? INT_MIN: INT_MAX;
	vector<vector<int>> final_combinations;


	for (int i=0; i<neighbours.size();i++)
	{
		pair<Board*,int> child_pair = generate_board(temp, neighbours[i], (1+depth)%2);
		Board* child = child_pair.first;

		int success = child_pair.second;
		success = min(3,success);

		int score = 0;
		
		if (success)
		{
			// cerr << "\n\n\n";
			// cerr << "Temp board is \n";
			// temp->print_board();
			// cerr << "Temp score is " << temp->score();
			// cerr << "Move is " << neighbours[i].first.first << " " << neighbours[i].first.second << " " << neighbours[i].second.first << " " << neighbours[i].second.second << endl;
			// cerr << "Child board is \n";
			// child->print_board();
			// cerr << "Child score is " << child->score();
			// cerr << "\n\n\n";
			int num_rings = polarity ? child->no_my_rings():child->no_opp_rings();
			vector<vector<int>> combinations = get_combinations(num_rings, success);

			// cerr << "Printing combinations \n";
			// for (int j=0; j<combinations.size();j++)
			// {
			// 	vector<int> rings = combinations[j];
			// 	for (int k = 0; k < rings.size(); ++k)
			// 	{
			// 		cerr << combinations[j][k] << " ";
			// 	}
			// 	cerr << endl;
			// }

			for (int j=0; j<combinations.size();j++)
			{
				Board* temp_com = new Board(child);
				vector<int> rings = combinations[j];
				// cerr << "After combination index " << j << endl;
				for (int k=0;k<rings.size();k++)
				{
					if (depth%2 == 0)
					{
						temp_com->remove_ring(temp_com->get_my_rings()->at(rings[k]-k));
					}
					else
					{
						temp_com->remove_ring(temp_com->get_opp_rings()->at(rings[k]-k));
					}
				}
				// cerr << "Board score " << temp_com->score() << endl;
				pair<int, vector<int> > move = alpha_beta(temp_com, depth+1, final_depth, counter, alpha, beta);

				score = move.first;

				if(depth%2 == 0)
				{
					alpha = max(alpha, score);
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
					beta = min(beta, score);
					if(score < res_score)
					{
						res_score = score;
						index_ring_removal = j;
						index = i;
						final_combinations = combinations;
					}	
				}

				if(alpha >= beta)
				{
					break;
				}
			}


		}
		else
		{
			pair<int, vector<int> > move = alpha_beta(child, depth+1, final_depth, counter, alpha, beta);
			score = move.first;
			
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
			// auto start = high_resolution_clock::now();
			// delete child;
			// auto stop = high_resolution_clock::now(); 
			// auto duration = duration_cast<microseconds>(stop - start); 
  
    		// cerr << "Time taken by delete "<< duration.count() << " microseconds" << endl; 

			if(alpha >= beta)
			{
				break;
			}
		}

		// if (depth == 0)
		// {
		// 	cerr << "Depth = " << depth << " Move is " << neighbours[i].first.first << " " << neighbours[i].first.second << " " << neighbours[i].second.first << " " << neighbours[i].second.second << " ";
		// 	cerr << score << "\n";
		// }
	}
	// cerr << "\n";

	
	vector<int> ret_vec(4);
	if(index_ring_removal != -1)
	{
		ret_vec.resize(4+final_combinations[index_ring_removal].size());
		ret_vec[0] = neighbours[index].first.first;
		ret_vec[1] = neighbours[index].first.second;
		ret_vec[2] = neighbours[index].second.first;
		ret_vec[3] = neighbours[index].second.second;
		
		// if(depth == 0)
		// {	
		// 	cerr << "Printing final combination at " << index_ring_removal << endl;
		// 	for (int i = 0; i < final_combinations[index_ring_removal].size(); ++i)
		// 	{
		// 		cerr << final_combinations[index_ring_removal][i] << " ";
		// 	}
		// 	cerr << endl;
		// }

		for (int i = 0; i < final_combinations[index_ring_removal].size(); ++i)
		{
			ret_vec[i+4] = final_combinations[index_ring_removal][i];
		}


	}
	else
	{
		ret_vec[0] = neighbours[index].first.first;
		ret_vec[1] = neighbours[index].first.second;
		ret_vec[2] = neighbours[index].second.first;
		ret_vec[3] = neighbours[index].second.second;
	}
	// cerr << "Printing ret_vec" << endl;
	// for (int i = 0; i < ret_vec.size(); ++i)
	// {
	// 	cerr << ret_vec[i] << " ";
	// }
	// cerr << endl;
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

	
	for (int i=0;i<my_rings->size();i++)
	{
		Ring* current_ring = my_rings->at(i);
		pair<int,int> current_position = current_ring->get_position();
		
		for(int direction=0; direction<6;direction++)
		{
			vector<pair<int,int>> possible_positions = my_board->get_possible_positions(current_position, direction);
			
			for (int j=0;j<possible_positions.size();j++)
			{
				pair<pair<int,int>, pair<int,int>> elem;
				elem.first = current_position;
				elem.second = possible_positions[j];
				neighbours.push_back(elem);
			}
		}
	}

	return neighbours;
}

pair<Board*,int> Solver::generate_board(Board* my_board, pair<pair<int,int>, pair<int,int>> neighbour, int polarity)
{
	Board* new_board = new Board(my_board);
	
	pair<int, int> ring_pos = neighbour.first;
	int	index = get_board_index(ring_pos);
	
	Ring* ring = (Ring*)new_board->get_configuration(index).second;

	pair<int,int> final_position = neighbour.second;
	new_board->move_ring(ring, final_position.first, final_position.second);

	vector<int> to_remove_markers = new_board->detect_success(polarity);
	
	int success = 0;
	while(to_remove_markers.size() > 0)
	{
		success++;
	
		pair<int, int> one_end = make_pair(to_remove_markers[0], to_remove_markers[1]);
		pair<int, int> second_end = make_pair(to_remove_markers[2], to_remove_markers[3]);
	
		new_board->remove_markers(one_end, second_end, polarity);
		to_remove_markers = new_board->detect_success(polarity);
	}

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

