#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<fstream>
#include<vector>
#include <unordered_map>
#include <queue> 
#include "Ring.h"
#include "Marker.h"
#include "Util.h"
using namespace std;

class Board {
private:

    vector<Marker*> my_markers;
    vector<Ring*> my_rings;
    vector< pair< char, void*> > configuration; 
    int board_size;

public:
    Board(int);
    Board(Board* base_board);
    int no_my_rings();
    void add_ring(Ring*);
    void add_marker(Marker*);
    pair<char, void*> get_configuration(int);
    void set_configuration(pair<char, void*>, int);

    int get_board_size();
    bool out_of_bounds(pair<int,int>);

    vector<pair <int, int> > get_possible_positions(pair<int, int> current_position, int direction);

    int score();
};

#endif  /* BOARD_H */

