#include <iostream>
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
	
	if(player_id == 2) 
	{
		string move_opp = "";
		while(move_opp == "")
		{
			getline(cin, move_opp);
		}
		string my_move = "";
		cerr << "CERR: Enter your move\n";
		getline(cin, my_move);
		// Register opponent move in our board: Krunal
		
		while(true) 
		{
			string move_opp = "";
			while(move_opp == "")
			{
				getline(cin, move_opp);
			}
			string my_move = "";
			cerr << "CERR: Enter your move\n";
			getline(cin, my_move);
			cerr << "CERR: Your move" << my_move << "\n";
			cout << my_move;
		}
	}   
	else if(player_id == 1) 
	{
		while(true) 
		{
			string my_move = "";
			cerr << "CERR: Enter your move\n";
			getline(cin, my_move);
			cerr << "CERR: Your move" << my_move << "\n";
			cout << my_move;

			string move_opp = "";
			while(move_opp == "")
			{
				getline(cin, move_opp);
			}
		}
	}
	return 0;
}