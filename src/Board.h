#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<fstream>
#include<vector>
#include <unordered_map>
#include "Ring.h"
#include "Marker.h"
using namespace std;

class Board {
private:

    vector<Marker*> markers;
    vector<Ring*> rings;
    vector<Marker*> my_markers;
    vector<Ring*> my_rings;

    unordered_map<int, int> filled_pos;
    
public:
    Board();
    Board(Board* base_board);
    int no_my_rings();
    void add_ring(Ring* ring);
    
    
};

#endif  /* BOARD_H */

