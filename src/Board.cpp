#include "Board.h"

Board::Board(int board_size)
{
    board_size = board_size;
}

Board::Board(Board* base_board)
{
    board_size = base_board->get_board_size();
    // add markers, rings to vector: Krunal 
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

int Board::get_board_size()
{
    return board_size;
}

void Board::add_ring(Ring* ring)
{
	cerr << "CERR: ring polarity = " << ring->get_polarity() << endl;
	if(ring->get_polarity() == 1)
	{
		cerr << "CERR: Adding ring to MY board\n";
		my_rings.push_back(ring);
		rings.push_back(ring);
	}
	else
	{
		rings.push_back(ring);
	}
}