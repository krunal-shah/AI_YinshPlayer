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

    vector<Marker> markers;
    vector<Ring> rings;

    
public:
    Board();
    
    
};

#endif  /* BOARD_H */

