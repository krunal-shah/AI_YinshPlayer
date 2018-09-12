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
	string a = "       P 7947 794 P      144445 141    T 144 14     ";
	vector< pair< string, pair< int, int > > > b;
	cout << a << endl;
	b = fill_moves(a);
	for(auto it:b)
	{
		cout << it.first << endl;
		cout << it.second.first << endl;
		cout << it.second.second << endl;
	}
}