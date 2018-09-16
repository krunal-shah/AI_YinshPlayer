#include <vector>
#include<iostream>
#include<fstream>

using namespace std;

vector<pair<string, pair< int, int> > > fill_moves(string m);
int fill_move(string m, string &ch, int &a, int &b);
int get_board_index(pair<int,int>);
int get_board_index(int radius, int offset);
pair<int, int> get_next_position(pair<int, int> current_position, int direction);
int get_direction(pair<int,int> initial_position, pair<int,int> final_position);