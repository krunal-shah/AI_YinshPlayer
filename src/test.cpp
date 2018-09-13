#include <iostream>
#include <string.h>
#include <math.h>
// #include <bits/stdc++.h>
#include <unordered_map>
#include "Util.h"

#define vit vector<int>::iterator
#define vec vector<int>
#define itr ::iterator
#define pb push_back
#define mp make_pair
#define mod(a,b) (a%b+b)%b

/*
vector	void push_back	pop_back
		insert(itr)	erase(itr)
		ITERATOR:
		CONST ITR vec.begin(), vec.end()
		*itr returns the value stored

map 	ret itr .find(Key)
<Key,T> map[key] = T


stack	void push pop
		ret top

queue	void push pop
		ret front

sort(start itr, end itr)

*/
using namespace std;

int main(int argv, char* args[])
{
	// pair<int, int> get_next_position(pair<int, int> current_position, int direction)
	int dir = 4;
	pair<int, int> one = make_pair(2,0);
	pair<int, int> onea = get_next_position(one, dir);
	cout << one.first << ", " << one.second << " -- " << onea.first << ", " << onea.second << endl;

	pair<int, int> two = make_pair(2,2);
	pair<int, int> twoa = get_next_position(two, dir);
	cout << two.first << ", " << two.second << " -- " << twoa.first << ", " << twoa.second << endl;

	two = make_pair(2,4);
	twoa = get_next_position(two, dir);
	cout << two.first << ", " << two.second << " -- " << twoa.first << ", " << twoa.second << endl;

	two = make_pair(2,6);
	twoa = get_next_position(two, dir);
	cout << two.first << ", " << two.second << " -- " << twoa.first << ", " << twoa.second << endl;

	two = make_pair(2,8);
	twoa = get_next_position(two, dir);
	cout << two.first << ", " << two.second << " -- " << twoa.first << ", " << twoa.second << endl;

	two = make_pair(2,10);
	twoa = get_next_position(two, dir);
	cout << two.first << ", " << two.second << " -- " << twoa.first << ", " << twoa.second << endl;

	// pair<int, int> one = make_pair(2,4);
	// pair<int, int> onea = get_next_position(one, 0);
	// cout << one.first << ", " << one.second << " -- " << onea.first << ", " << onea.second << endl;

	// pair<int, int> one = make_pair(2,4);
	// pair<int, int> onea = get_next_position(one, 0);
	// cout << one.first << ", " << one.second << " -- " << onea.first << ", " << onea.second << endl;
}