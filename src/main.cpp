#include <iostream>
#include "Solver.h"
#include <stdlib.h>

using namespace std;

// Sample C++ Code 
int main(int argc, char** argv) 
{
	
	int player_id, board_size, time_limit;
	string move;

	// Get input from server about game specifications
	cin >> player_id >> board_size >> time_limit;
	int turn = 1;
	int moves = 0;
	
	Solver* solver = new Solver(player_id, board_size, time_limit);
	
	if(player_id == 2) 
	{
		// Get other player's move
		cin >> move; 

		// Register opponent move in our board: Krunal
		
		while(true) 
		{
			cout<<"P 1 0"<<endl;
			cin >> move;
		}
	}   
	else if(player_id == 1) 
	{
		while(true) 
		{
			string move_my = solver->move();
			cout << move_my;
			turn = 2;

			if(moves ==  10)
				return 0;

			string move_opp = "";
			while(move_opp == "")
			{
				getline(cin, move_opp);
			}
			moves++;

			turn = 1;
		}
	}
	return 0;
}