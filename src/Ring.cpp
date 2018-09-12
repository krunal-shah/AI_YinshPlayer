#include "Ring.h"

Ring::Ring(int a, int b, int polarity)
{
    pos = make_pair(a, b);
    polarity = polarity;
}

pair<int, int> Ring::get_position()
{
	return pos;
}

int Ring::get_polarity()
{
	return polarity;
}