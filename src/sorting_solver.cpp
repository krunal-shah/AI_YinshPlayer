// vector<pair<pair<int,int>, pair<int,int>>> neighbours = Solver::get_neighbours(temp, (1+depth)%2);
	// int polarity = (1+depth)%2;

	// vector<pair<pair<int, int>, pair<Board*,int>>> neighbour_boards(neighbours.size());

	// for (int i = 0; i < neighbours.size(); ++i)
	// {
	// 	pair<Board*,int> child = generate_board(temp, neighbours[i], (1+depth)%2);
	// 	int child_score = child.first->score();
	// 	neighbour_boards[i] = make_pair(make_pair(child_score, i), make_pair(child.first,child.second));
	// }

	// sort(neighbour_boards.rbegin(), neighbour_boards.rend());

	// // cerr << "Sorted scores" << endl;
	// // for (int i = 0; i < neighbour_boards.size(); ++i)
	// // {
	// // 	cerr << i << ". " << neighbour_boards[i].first.first << endl;
	// // }

	// // cerr << "Exiting get_neighbours" << endl;
	// int index = 0;
	// int index_ring_removal = -1;
	// int res_score = depth%2 == 0 ? INT_MIN: INT_MAX;
	// vector<vector<int>> final_combinations;


	// for (int i=0; i<neighbour_boards.size();i++)
	// {
	// 	pair<Board*,int> child_pair = neighbour_boards[i].second;
	// 	Board* child = child_pair.first;

	// 	int success = child_pair.second;
	// 	success = min(3,success);

	// 	int score = 0;
		
	// 	if (success)
	// 	{
	// 		int num_rings = polarity ? child->no_my_rings():child->no_opp_rings();
	// 		vector<vector<int>> combinations = get_combinations(num_rings, success);

	// 		for (int j=0; j<combinations.size();j++)
	// 		{
	// 			Board* temp_com = new Board(child);
	// 			vector<int> rings = combinations[j];
				
	// 			for (int k=0;k<rings.size();k++)
	// 			{
	// 				if (depth%2 == 0)
	// 				{
	// 					temp_com->remove_ring(temp_com->get_my_rings()->at(rings[k]-k));
	// 				}
	// 				else
	// 				{
	// 					temp_com->remove_ring(temp_com->get_opp_rings()->at(rings[k]-k));
	// 				}
	// 			}
				
	// 			pair<int, vector<int> > move = alpha_beta(temp_com, depth+1, final_depth, counter, alpha, beta);

	// 			score = move.first;
	// 			if(depth == 0)
	// 			{
	// 				if(temp_com->get_my_rings()->size() == board_size-3)
	// 					score = INT_MAX - 5;
	// 				else if(temp_com->get_opp_rings()->size() == board_size-3)
	// 					score = INT_MIN + 5;
	// 			}

	// 			if(depth%2 == 0)
	// 			{
	// 				alpha = max(alpha, score);
	// 				if(score > res_score)
	// 				{
	// 					res_score = score;
	// 					index_ring_removal = j;
	// 					index = i;
	// 					final_combinations = combinations;
	// 				}
	// 			}
	// 			else
	// 			{
	// 				beta = min(beta, score);
	// 				if(score < res_score)
	// 				{
	// 					res_score = score;
	// 					index_ring_removal = j;
	// 					index = i;
	// 					final_combinations = combinations;
	// 				}	
	// 			}

	// 			if(alpha >= beta)
	// 			{
	// 				break;
	// 			}
	// 		}


	// 	}
	// 	else
	// 	{
	// 		pair<int, vector<int> > move = alpha_beta(child, depth+1, final_depth, counter, alpha, beta);
	// 		score = move.first;
			
	// 		if(depth%2 == 0)
	// 		{
	// 			alpha = max(alpha, score);
	// 			if(score > res_score)
	// 			{
	// 				res_score = score;
	// 				index = i;
	// 				index_ring_removal = -1;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			beta = min(beta, score);
	// 			if(score < res_score)
	// 			{
	// 				res_score = score;
	// 				index = i;
	// 				index_ring_removal = -1;
	// 			}	
	// 		}
			
	// 		if(alpha >= beta)
	// 		{
	// 			break;
	// 		}
	// 	}

	// 	// if (depth == 0)
	// 	// {
	// 	// 	cerr << "Depth = " << depth << " Move is " << neighbours[i].first.first << " " << neighbours[i].first.second << " " << neighbours[i].second.first << " " << neighbours[i].second.second << " ";
	// 	// 	cerr << score << "\n";
	// 	// }
	// }
	
	// vector<int> ret_vec(4);
	// if(index_ring_removal != -1)
	// {
	// 	// ret_vec.resize(4+final_combinations[index_ring_removal].size());
	// 	// ret_vec[0] = neighbours[index].first.first;
	// 	// ret_vec[1] = neighbours[index].first.second;
	// 	// ret_vec[2] = neighbours[index].second.first;
	// 	// ret_vec[3] = neighbours[index].second.second;

	// 	ret_vec.resize(4+final_combinations[index_ring_removal].size());
	// 	ret_vec[0] = neighbours[neighbour_boards[index].first.second].first.first;
	// 	ret_vec[1] = neighbours[neighbour_boards[index].first.second].first.second;
	// 	ret_vec[2] = neighbours[neighbour_boards[index].first.second].second.first;
	// 	ret_vec[3] = neighbours[neighbour_boards[index].first.second].second.second;
		
	// 	// if(depth == 0)
	// 	// {	
	// 	// 	cerr << "Printing final combination at " << index_ring_removal << endl;
	// 	// 	for (int i = 0; i < final_combinations[index_ring_removal].size(); ++i)
	// 	// 	{
	// 	// 		cerr << final_combinations[index_ring_removal][i] << " ";
	// 	// 	}
	// 	// 	cerr << endl;
	// 	// }

	// 	for (int i = 0; i < final_combinations[index_ring_removal].size(); ++i)
	// 	{
	// 		ret_vec[i+4] = final_combinations[index_ring_removal][i];
	// 	}


	// }
	// else
	// {
	// 	ret_vec[0] = neighbours[neighbour_boards[index].first.second].first.first;
	// 	ret_vec[1] = neighbours[neighbour_boards[index].first.second].first.second;
	// 	ret_vec[2] = neighbours[neighbour_boards[index].first.second].second.first;
	// 	ret_vec[3] = neighbours[neighbour_boards[index].first.second].second.second;
	// }


	