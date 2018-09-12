#include "Board.h"

Board::Board()
{
    
}

Board::Board(Board* base_board)
{
    for(auto it: base_board->filled_pos)
    {
    	filled_pos[it.first] = it.second;
    }

    for(auto it: base_board->markers)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Marker* temp_marker = new Marker(temp_pos.first, temp_pos.second, it->get_polarity());
    	markers.push_back(temp_marker);
    }
    for(auto it: base_board->rings)
    {
    	pair<int, int> temp_pos = it->get_position();
    	Ring* temp_ring = new Ring(temp_pos.first, temp_pos.second, it->get_polarity());
    	rings.push_back(temp_ring);
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

void Board::add_ring(Ring* ring)
{
	my_rings.push_back(ring);
}