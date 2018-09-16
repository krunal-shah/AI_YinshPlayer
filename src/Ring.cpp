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

void Ring::move(int x, int y)
{
	pos = make_pair(x,y);
}