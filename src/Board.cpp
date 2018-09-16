#include "Board.h"


Board::Board(int bsize)
{
    board_size = bsize;
    cerr << "Constructor board_size " << board_size << endl;;
    int max_positions = 2*board_size*(board_size-1) + 6*board_size + 1;
    configuration.resize(max_positions);
    
    void* nullp = NULL;
    pair<char, void*> temp = make_pair('n', nullp);
    fill(configuration.begin(), configuration.end(), temp);
}

Board::Board(Board* base_board)
{
    board_size = base_board->get_board_size();
    
    for(int i=0; i < configuration.size(); i++)
    {
    	pair<char, void*> temp = make_pair(configuration[i].first, configuration[i].second);
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

}

int Board::no_my_rings()
{
	return my_rings.size();
}

bool Board::out_of_bounds(pair<int,int> position)
{
    int radius = position.first;
    int offset = position.second;

    cerr << "Entering out of bound for " << radius << " " << offset << endl; 

    if(radius == 0)
    {
    	cerr << "Exiting out of bound for " << radius << " " << offset << endl;
    	return false;
	}

    if (radius>board_size || (radius == board_size && offset%board_size == 0))
    {
    	cerr << "Board size == " << board_size;
    	cerr << "Exiting out of bound for true " << radius << " " << offset << endl;
    	return true;
	}
	cerr << "Exiting out of bound for " << radius << " " << offset << endl;
    return false;
}

int Board::score()
{
	vector< int > done(0);

	int score = 0;

	int upper = 4*board_size-1;
	int lower = 2*board_size+1;

	queue<int> lastfive;
	int current_index;
	pair<char, void*> current_elem;
	pair<char, void*> popped_elem;
	int elems_lastfive = 0;
	int rings_lastfive = 0;
	
	pair<int, int> current_pos;
	pair<int, int> next_pos;

	
	for (int direction = 0; direction < 3; ++direction)
	{
		// cerr << "CERR: Direction " << direction << endl;
		for (int offset = lower; offset <= upper; offset++)
		{
			current_pos = make_pair(board_size, offset);

			while(!out_of_bounds(current_pos))
			{
				// cerr << "CERR: At position: " << current_pos.first << " " << current_pos.second << endl;
				cerr << "Value of elems_lastfive " << elems_lastfive << " " << ", value of rings_lastfive " << rings_lastfive << endl;
				next_pos = get_next_position(current_pos, direction);
				cerr << "At check 1" << endl;
				current_index = get_board_index(current_pos); 
				cerr << "At check 2" << endl;
				current_elem = configuration[current_index];
				cerr << "At check 3" << endl;

				if(lastfive.size() == 5)
				{
					popped_elem = configuration[lastfive.front()];
					lastfive.pop();
					
					if(popped_elem.first == 'R')
					{
						Ring* popped_ring = (Ring*)popped_elem.second;
						if(popped_ring->get_polarity() == 1)
							elems_lastfive --;
						else
							elems_lastfive ++;

						rings_lastfive --;
					}
					else if(popped_elem.first == 'M')
					{
						Marker* popped_marker = (Marker*)popped_elem.second;
						if(popped_marker->get_polarity() == 1)
							elems_lastfive --;
						else
							elems_lastfive ++;
					}
				}


				if(current_elem.first == 'R')
				{
					Ring* current_ring = (Ring*)current_elem.second;
					if(current_ring->get_polarity() == 1)
						elems_lastfive ++;
					else
						elems_lastfive --;

					rings_lastfive ++;
				}
				else if(current_elem.first == 'M')
				{
					Marker* current_marker = (Marker*)current_elem.second;
					if(current_marker->get_polarity() == 1)
						elems_lastfive ++;
					else
						elems_lastfive --;
				}

				lastfive.push(current_index);
				current_pos = next_pos;
				if(elems_lastfive == 5 && rings_lastfive <= 1)
				{
					score += 5;
				}
				else if(elems_lastfive == -5 && rings_lastfive <= 1)
				{
					score -= 5;
				}
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

	current_position = get_next_position(current_position, direction);
	bool marker = false;
	while (!out_of_bounds(current_position))
	{
		int index = get_board_index(current_position);
		pair<char,void*> configuration = get_configuration(index);
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

		current_position = get_next_position(current_position, direction);

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
}

void Board::add_marker(Marker* piece)
{
	pair<int, int> pos = piece->get_position();
	int index = get_board_index(pos);

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

void Board::set_configuration(pair<char, void*> temp, int i)
{
	configuration[i] = temp;
}
vector<Ring*> Board::get_my_rings()
{
	return my_rings;
}