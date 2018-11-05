#include <iostream>
#include "Solver.h"
#include <stdlib.h>
#include <cstring>

using namespace std;

// Sample C++ Code 
int main(int argc, char** argv) 
{
	

	// Get input from server about game specifications
	// cin >> move;
	
	int seed1 = stoi(argv[1]), seed2 = stoi(argv[2]);
	int player_id = 1, board_size = 6, time_limit = 150, consecutive_rings = 5;
	int turn = 1;
	int moves = 0;
	Solver* one = new Solver(player_id, board_size, time_limit, consecutive_rings, seed1);

	player_id = 2;
	Solver* two = new Solver(player_id, board_size, time_limit, consecutive_rings, seed2);
	
	player_id = 1;
	string move = "";
	int one_remove = 0, two_remove = 0;
	while(true)
	{
		if(player_id == 1) 
		{
			move = one->move();
			move = move.erase(move.length()-1,1);
			cout << "1 " << move << endl;
			two->make_opp_move(move);
			player_id = 2;
			for (int i = 0; i < move.length(); ++i)
			{
				if(move[i] == 'X')
					one_remove++;
			}
		}   
		else
		{
			move = two->move();
			move = move.erase(move.length()-1,1);
			cout << "2 " << move << endl;
			one->make_opp_move(move);
			player_id = 1;
			for (int i = 0; i < move.length(); ++i)
			{
				if(move[i] == 'X')
					two_remove++;
			}
		}
		if(one_remove == 3 || two_remove == 3)
		{
			cout << "%%**" << endl;
			break;
		}
	}
	return 0;
}