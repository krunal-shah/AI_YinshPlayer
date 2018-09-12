#ifndef MARKER_H
#define MARKER_H

#include<iostream>
#include<fstream>
using namespace std;

class Marker {
private:

    pair<int, int> pos;
    int polarity; // 1 is ours, 0 is opp

public:
    Marker(int, int, int);
    pair<int, int> get_position();
	int get_polarity();    
    
};

#endif  /* MARKER_H */

