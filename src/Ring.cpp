#include "Ring.h"

Ring::Ring(int a, int b, int p)
{
    pos = make_pair(a, b);
    polarity = p;
}

pair<int, int> Ring::get_position()
{
	return pos;
}

int Ring::get_polarity()
{
	return polarity;
}

string Ring::my_type()
{
	return "ring";
}