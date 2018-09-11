#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<fstream>
#include<vector>
#include "Ring.h"
#include "Marker.h"
using namespace std;

class Board {
private:

    vector<Marker> my_markers;
    vector<Ring> my_rings;

    vector<Marker> opp_markers;
    vector<Ring> opp_rings;

public:
    Board();
    
    
};

#endif  /* BOARD_H */

