#include "Board.h"


Board::Board(int bsize)
{
    board_size = bsize;
    int max_positions = 3*board_size*(board_size-1) + 6*board_size + 1;
    configuration.resize(max_positions);
    
    void* nullp = NULL;
    pair<char, void*> temp = make_pair('n', nullp);
    fill(configuration.begin(), configuration.end(), temp);
}

Board::Board(Board* base_board)
{
    board_size = base_board->get_board_size();
    int max_positions = 3*board_size*(board_size-1) + 6*board_size + 1;
    configuration.resize(max_positions);
    
    void* nullp = NULL;
    pair<char, void*> temp = make_pair('n', nullp);
    fill(configuration.begin(), configuration.end(), temp);
    // for(int i=0; i < configuration.size(); i++)
    // {
    // 	pair<char, void*> temp = base_board->get_configuration(i);
    // 	configuration[i] = temp;
    // }

    for(auto it: base_board->my_markers)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Marker* temp_marker = new Marker(temp_pos.first, temp_pos.second, it->get_polarity());
    	int index = get_board_index(temp_pos);
    	configuration[index] = make_pair('m', temp_marker);
    	my_markers.push_back(temp_marker);
    }

    for(auto it: base_board->my_rings)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Ring* temp_ring = new Ring(temp_pos.first, temp_pos.second, it->get_polarity());
    	int index = get_board_index(temp_pos);
    	configuration[index] = make_pair('r', temp_ring);
    	my_rings.push_back(temp_ring);
    }

    for(auto it: base_board->opp_rings)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Ring* temp_ring = new Ring(temp_pos.first, temp_pos.second, it->get_polarity());
    	int index = get_board_index(temp_pos);
    	configuration[index] = make_pair('r', temp_ring);
    	opp_rings.push_back(temp_ring);
    }

    for(auto it: base_board->opp_markers)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Marker* temp_marker = new Marker(temp_pos.first, temp_pos.second, it->get_polarity());
    	int index = get_board_index(temp_pos);
    	configuration[index] = make_pair('m', temp_marker);
    	opp_markers.push_back(temp_marker);
    }
}

int Board::no_my_rings()
{
	return my_rings.size();
}

bool Board::out_of_bounds(pair<int,int> position)
{
    int radius = position.first;
    int offset = position.second;

    if(radius == 0)
    {
    	return false;
	}

    if (radius>board_size || (radius == board_size && offset%board_size == 0))
    {
    	return true;
	}
	return false;
}

int Board::score()
{
	int score = 0;

	int upper = 4*board_size-1;
	int lower = 2*board_size+1;

	queue<int> lastfive;
	pair<char, void*> current_elem;
	pair<char, void*> popped_elem;
	int elems_lastfive = 0;
	int rings_lastfive = 0;
	
	pair<int, int> current_pos;
	int current_index;
	
	
	for (int direction = 0; direction < 3; ++direction)
	{
		// cerr << "CERR: Direction " << direction << endl;
		for (int offset = lower; offset <= upper; offset++)
		{
			current_pos = make_pair(board_size, offset);

			while(!out_of_bounds(current_pos))
			{
				// cerr << "CERR: At position: " << current_pos.first << " " << current_pos.second << endl;
				// cerr << "Value of elems_lastfive " << elems_lastfive << " " << ", value of rings_lastfive " << rings_lastfive << endl;
				// cerr << "At check 1" << endl;
				current_index = get_board_index(current_pos); 
				// cerr << "At check 2" << endl;
				current_elem = configuration[current_index];
				// cerr << "At check 3" << endl;

				if(lastfive.size() == 5)
				{
					popped_elem = configuration[lastfive.front()];
					lastfive.pop();
					
					if(popped_elem.first == 'r')
					{
						Ring* popped_ring = (Ring*)popped_elem.second;
						if(popped_ring->get_polarity() == 1)
							elems_lastfive --;
						else
							elems_lastfive ++;

						rings_lastfive --;
					}
					else if(popped_elem.first == 'm')
					{
						Marker* popped_marker = (Marker*)popped_elem.second;
						if(popped_marker->get_polarity() == 1)
							elems_lastfive --;
						else
							elems_lastfive ++;
					}
				}


				if(current_elem.first == 'r')
				{
					Ring* current_ring = (Ring*)current_elem.second;
					if(current_ring->get_polarity() == 1)
						elems_lastfive ++;
					else
						elems_lastfive --;

					rings_lastfive ++;
				}
				else if(current_elem.first == 'm')
				{
					Marker* current_marker = (Marker*)current_elem.second;
					if(current_marker->get_polarity() == 1)
						elems_lastfive ++;
					else
						elems_lastfive --;
				}

				lastfive.push(current_index);

				score += elems_lastfive;
				if(elems_lastfive == 5 && rings_lastfive <= 1)
				{
					score += 100;
				}
				else if(elems_lastfive == -5 && rings_lastfive <= 1)
				{
					score -= 100;
				}
				
				current_pos = get_next_position(current_pos, direction);;
			}
			// cerr << "Exited out of bounds for " << current_pos.first << " " << current_pos.second << endl;
		}

		upper += board_size; // upper could be 6*board_size
		lower += board_size;
	} 

	return score;
}

vector<vector<int>> Board::detect_success()
{
	vector<vector<int>> ans;
	int upper = 4*board_size-1;
	int lower = 2*board_size+1;

	queue<int> lastfive;
	pair<char, void*> current_elem;
	pair<char, void*> popped_elem;
	int elems_lastfive = 0;
	int rings_lastfive = 0;
	
	pair<int, int> current_pos;
	int current_index;
	
	
	for (int direction = 0; direction < 3; ++direction)
	{
		// cerr << "CERR: Direction " << direction << endl;
		for (int offset = lower; offset <= upper; offset++)
		{
			current_pos = make_pair(board_size, offset);

			while(!out_of_bounds(current_pos))
			{
				// cerr << "CERR: At position: " << current_pos.first << " " << current_pos.second << endl;
				// cerr << "Value of elems_lastfive " << elems_lastfive << " " << ", value of rings_lastfive " << rings_lastfive << endl;
				// cerr << "At check 1" << endl;
				current_index = get_board_index(current_pos); 
				// cerr << "At check 2" << endl;
				current_elem = configuration[current_index];
				// cerr << "At check 3" << endl;

				if(lastfive.size() == 5)
				{
					popped_elem = configuration[lastfive.front()];
					lastfive.pop();
					
					if(popped_elem.first == 'r')
					{
						Ring* popped_ring = (Ring*)popped_elem.second;
						if(popped_ring->get_polarity() == 1)
							elems_lastfive --;
						else
							elems_lastfive ++;

						rings_lastfive --;
					}
					else if(popped_elem.first == 'm')
					{
						Marker* popped_marker = (Marker*)popped_elem.second;
						if(popped_marker->get_polarity() == 1)
							elems_lastfive --;
						else
							elems_lastfive ++;
					}
				}


				if(current_elem.first == 'r')
				{
					Ring* current_ring = (Ring*)current_elem.second;
					if(current_ring->get_polarity() == 1)
						elems_lastfive ++;
					else
						elems_lastfive --;

					rings_lastfive ++;
				}
				else if(current_elem.first == 'm')
				{
					Marker* current_marker = (Marker*)current_elem.second;
					if(current_marker->get_polarity() == 1)
						elems_lastfive ++;
					else
						elems_lastfive --;
				}

				lastfive.push(current_index);

				cerr << "Detect" << endl;
				cerr << current_pos.first << " " << current_pos.second << " " << direction << " " << elems_lastfive << " " << rings_lastfive << endl;

				if(elems_lastfive == 5 && rings_lastfive == 0)
				{
					vector<int> temp_ans(4);
					Marker* cur_mark = (Marker*)(current_elem.second);
					Marker* sec_mark = (Marker*)(get_configuration(lastfive.front()).second);
					temp_ans[0] = cur_mark->get_position().first;
					temp_ans[1] = cur_mark->get_position().second;
					temp_ans[2] = sec_mark->get_position().first;
					temp_ans[3] = sec_mark->get_position().second;
					ans.push_back(temp_ans);
				}
				
				current_pos = get_next_position(current_pos, direction);;
			}
			// cerr << "Exited out of bounds for " << current_pos.first << " " << current_pos.second << endl;
		}

		upper += board_size; // upper could be 6*board_size
		lower += board_size;
	} 

	return ans;
}


vector< pair<int, int> > Board::get_possible_positions(pair<int, int> current_position, int direction)
{
	int radius = current_position.first;
	int offset = current_position.second;
	vector<pair<int,int>> positions;

	// cerr<<"hello"<<endl;
	// cerr<<"position "<<current_position.first<<" "<<current_position.second<<" "<<direction<<endl;
	current_position = get_next_position(current_position, direction);
	// cerr<<"hello?"<<endl;
	bool marker = false;
	int count = 0;
	// cerr<<"position "<<current_position.first<<" "<<current_position.second<<endl;
	while (!out_of_bounds(current_position))
	{	
		// cerr << "Currently at " << current_position.first << " " << current_position.second << endl;
		// cerr<<"out of?"<<endl;
		// cerr<<count++<<endl;
		int index = get_board_index(current_position);
		// cerr<<index<<endl;
		// cerr<<"out of!"<<endl;
		pair<char,void*> configuration = get_configuration(index);
		// cerr<<"get"<<endl;
		if (configuration.first == 'n')
		{
			positions.push_back(current_position);
			if(marker)
				break;
		}
		else if (configuration.first == 'm')
			marker = true;
		else
			break;
		// cerr<<"hello"<<endl;
		current_position = get_next_position(current_position, direction);
		// cerr<<"hello?"<<endl;

	}
	// cerr<<endl;

	return positions;

}

void Board::add_ring(Ring* piece)
{
	pair<int, int> pos = piece->get_position();
	int index = get_board_index(pos);

	pair<char, void*> temp = make_pair('r', piece);
	configuration[index] = temp;
	
	if(piece->get_polarity() == 1)
	{
		my_rings.push_back(piece);
	}
	else
	{
		opp_rings.push_back(piece);
	}
}

void Board::add_marker(Marker* piece)
{
	pair<int, int> pos = piece->get_position();
	int index = get_board_index(pos);

	// cerr << "Putting marker at " << pos.first << " " << pos.second << " index = " << index << endl;
	pair<char, void*> temp = make_pair('m', piece);
	configuration[index] = temp;
	
	if(piece->get_polarity() == 1)
	{
		my_markers.push_back(piece);
	}
	else
	{
		opp_markers.push_back(piece);
	}
}

int Board::get_board_size()
{
    return board_size;
}

pair<char, void*> Board::get_configuration(int i)
{
	return configuration[i];
}

void Board::set_configuration(char ch, void* ptr, int i)
{
	// cerr << "Playing with config at " << i << endl;
	configuration[i] = make_pair(ch, ptr);
	// cerr << "New config " << configuration[i].first << endl;
}
vector<Ring*>* Board::get_my_rings()
{
	return &my_rings;
}
vector<Ring*>* Board::get_opp_rings()
{
	return &opp_rings;
}
void Board::print_board()
{
	// vector<Marker*> my_markers;
	// vector<Ring*> my_rings;
	// vector<Ring*> opp_rings;
	// vector< pair< char, void*> > configuration; 
	// int board_size;

	cerr << "My markers" << endl;
	for (int i = 0; i < my_markers.size(); ++i)
	{
		pair<int, int> pos = my_markers[i]->get_position();
		cerr << "Marker " << i << " at " << pos.first << " " << pos.second << endl;
	}

	cerr << "My rings" << endl;
	for (int i = 0; i < my_rings.size(); ++i)
	{
		pair<int, int> pos = my_rings[i]->get_position();
		cerr << "Ring " << i << " at " << pos.first << " " << pos.second << endl;
	}

	cerr << "Opp rings" << endl;
	for (int i = 0; i < opp_rings.size(); ++i)
	{
		pair<int, int> pos = opp_rings[i]->get_position();
		cerr << "Ring " << i << " at " << pos.first << " " << pos.second << endl;
	}

	cerr << "Opp markers" << endl;
	for (int i = 0; i < opp_markers.size(); ++i)
	{
		pair<int, int> pos = opp_markers[i]->get_position();
		cerr << "Marker " << i << " at " << pos.first << " " << pos.second << endl;
	}

	cerr << "Configuration " << configuration.size() << endl;
	for (int i = 0; i < configuration.size(); ++i)
	{
		pair< char, void*> pos = configuration[i];
		// cerr << pos.first << endl;
		if(pos.first == 'r')
		{
			// cerr << "here" << endl;
			Ring* ring = (Ring*)pos.second;
			cerr << "ring at " << ring->get_position().first << " " << ring->get_position().second << " at index " << i << " polarity = " << ring->get_polarity() << endl;
		}
		else if(pos.first == 'm')
		{
			// cerr << "here" << endl;
			Marker* marker = (Marker*)pos.second;
			cerr << "marker at " << marker->get_position().first << " " << marker->get_position().second << " at index " << i << " polarity = " << marker->get_polarity() << endl;
		}
	}
}

void Board::move_ring(Ring* ring, int a, int b)
{
	pair<int, int> ring_pos = ring->get_position();
	// cerr << "polarity of ring trying to move " << ring->get_polarity() << endl;
	Marker* marker = new Marker(ring_pos.first, ring_pos.second, ring->get_polarity());

	int index = get_board_index(a,b);
	// cerr << "Trying to move ring to " << a << " " << b << " from " << ring_pos.first << " " << ring_pos.second << endl;
	set_configuration('r', ring, index);
	// cerr << "Set configuration" << endl;
	// print_board();
	pair<int,int> final_pos = make_pair(a,b);
	int direction = get_direction(ring_pos, final_pos);
	pair<int,int> current_position = get_next_position(ring_pos, direction);

	while(!out_of_bounds(current_position) && !(current_position == final_pos))
	{
		int ind = get_board_index(current_position);
		if( configuration[ind].first == 'm')
		{
			Marker* mark = (Marker*)configuration[ind].second;
			mark->flip_polarity();
			cerr << "Flipping " << mark->get_position().first << " " << mark->get_position().second << " " << mark->get_polarity() << endl;
		}
		current_position = get_next_position(current_position, direction);
	}

	ring->move(a,b);
	add_marker(marker);
	// cerr << "Moved marker" << endl;
	// print_board();	
}

void Board::move_ring(Ring* ring, pair<int, int> pos)
{
	move_ring(ring, pos.first, pos.second);
}

void Board::remove_markers(Marker* first_marker, Marker* last_marker)
{
	int polarity = first_marker->get_polarity();

	int direction = get_direction(first_marker->get_position(), last_marker->get_position());
	Marker* current_marker = first_marker;

	pair<int,int> current_position = current_marker->get_position();

	for (int i=0;i<5;i++)
	{
		int index = get_board_index(current_marker->get_position());
		set_configuration('n', NULL, index);

		vector<Marker*>* markers;
		if (polarity == 1)
			markers = &my_markers;
		else
			markers = &opp_markers;

		for (int i=0;i<markers->size();i++)
		{
			pair<int,int> pos = markers->at(i)->get_position();
			if(pos.first == current_position.first && pos.second == current_position.second)
				markers->erase(markers->begin()+i);
		}
		current_position = get_next_position(current_marker->get_position(), direction);
	}
}

void Board::remove_markers(pair<int,int> a, pair<int,int> b, int polarity)
{
	Marker* first_marker = new Marker(a.first,a.second,polarity);
	Marker* last_marker = new Marker(b.first,b.second,polarity);
	
	remove_markers(first_marker, last_marker);
}



void Board::remove_ring(Ring* ring)
{
	int polarity = ring->get_polarity();

	int index = get_board_index(ring->get_position());
	set_configuration('n', NULL, index);

	pair<int,int> position = ring->get_position();

	vector<Ring*>* rings;
	if (polarity == 1)
		rings = &my_rings;
	else
		rings = &opp_rings;
	
	for (int i=0;i<rings->size();i++)
	{
		pair<int,int> pos = rings->at(i)->get_position();
		if(pos.first == position.first && pos.second == position.second)
			rings->erase(rings->begin()+i);
	}

}