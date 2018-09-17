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
    vector<Ring*> opp_rings;
    vector<Marker*> opp_markers;
    vector< pair< char, void*> > configuration; 
    int board_size;
    int reality;

public:
    Board(int);
    Board(Board* base_board);
    int no_my_rings();
    void add_ring(Ring*);
    void add_marker(Marker*);
    
    pair<char, void*> get_configuration(int);
    void set_configuration(char, void*, int);
    
    vector<Ring*>* get_my_rings();
    vector<Ring*>* get_opp_rings();

    int get_board_size();
    bool out_of_bounds(pair<int,int>);

    vector<pair <int, int> > get_possible_positions(pair<int, int> current_position, int direction);

    int score();
    vector<int> detect_success();

    void print_board();
    void move_ring(Ring* ring, int a, int b);
    void move_ring(Ring* ring, pair<int,int>);

    void remove_markers(Marker* first_marker, Marker* last_marker);
    void remove_ring(Ring* ring);
    void remove_markers(pair<int,int> a, pair<int,int> b, int polarity);
    int get_direction(pair<int,int> initial_position, pair<int,int> final_position);

    void change_marker(Marker* marker);
};

#endif  /* BOARD_H */

