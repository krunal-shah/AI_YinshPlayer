#include "Board.h"

Board::Board(int board_size)
{
    board_size = board_size;
    int max_positions = 2*board_size*(board_size-1) + 6*board_size + 1;
    configuration.resize(max_positions);
    
    pair<char, void*> temp = make_pair('n', NULL);
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