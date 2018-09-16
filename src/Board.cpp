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
    
    for(int i=0; i < configuration.size(); i++)
    {
    	pair<char, void*> temp = base_board->get_configuration(i);
    	configuration[i] = temp;
    }

    for(auto it: base_board->my_markers)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Marker* temp_marker = new Marker(temp_pos.first, temp_pos.second, it->get_polarity());
    	my_markers.push_back(temp_marker);
    }

    for(auto it: base_board->my_rings)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Ring* temp_ring = new Ring(temp_pos.first, temp_pos.second, it->get_polarity());
    	my_rings.push_back(temp_ring);
    }

    for(auto it: base_board->opp_rings)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Ring* temp_ring = new Ring(temp_pos.first, temp_pos.second, it->get_polarity());
    	opp_rings.push_back(temp_ring);
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
	vector< int > done(0);

	int score = 0;

	int upper = 4*board_size-1;
	int lower = 2*board_size+1;

	queue<int> lastfive;
	int current_at;
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

				if(elems_lastfive == 5 && rings_lastfive <= 1)
				{
					score += 5;
				}
				else if(elems_lastfive == -5 && rings_lastfive <= 1)
				{
					score -= 5;
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

vector< pair<int, int> > Board::get_possible_positions(pair<int, int> current_position, int direction)
{
	int radius = current_position.first;
	int offset = current_position.second;
	vector<pair<int,int>> positions;

	// cerr<<"hello"<<endl;
	current_position = get_next_position(current_position, direction);
	// cerr<<"hello?"<<endl;
	bool marker = false;
	while (!out_of_bounds(current_position))
	{	
		// cerr<<"out of?"<<endl;
		int index = get_board_index(current_position);
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

	cerr << "Putting marker at " << pos.first << " " << pos.second << " index = " << index << endl;
	pair<char, void*> temp = make_pair('m', piece);
	configuration[index] = temp;
	
	if(piece->get_polarity() == 1)
	{
		my_markers.push_back(piece);
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
	cerr << "Playing with config at " << i << endl;
	configuration[i] = make_pair(ch, ptr);
	cerr << "New config " << configuration[i].first << endl;
}
vector<Ring*> Board::get_my_rings()
{
	return my_rings;
}
vector<Ring*> Board::get_opp_rings()
{
	return opp_rings;
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
	cerr << "polarity of ring trying to move " << ring->get_polarity() << endl;
	Marker* marker = new Marker(ring_pos.first, ring_pos.second, ring->get_polarity());

	int index = get_board_index(a,b);
	cerr << "Trying to move ring to " << a << " " << b << " from " << ring_pos.first << " " << ring_pos.second << endl;
	set_configuration('r', ring, index);
	// cerr << "Set configuration" << endl;
	// print_board();

	ring->move(a,b);
	add_marker(marker);
	cerr << "Moved marker" << endl;
	print_board();	
}

void Board::move_ring(Ring* ring, pair<int, int> pos)
{
	int a = pos.first;
	int b = pos.second;

	move_ring(ring, a, b);
}