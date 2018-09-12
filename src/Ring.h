#ifndef RING_H
#define RING_H

#include<iostream>
#include<fstream>
using namespace std;

class Ring {
private:

    pair<int, int> pos;
    bool polarity; // 1 is ours, 0 is opp

public:
    Ring(int a, int b, int polarity);
    pair<int, int> get_position();
	int get_polarity();    

};

#endif  /* RING_H */

