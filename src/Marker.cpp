#include "Marker.h"

Marker::Marker(int a, int b, int p)
{
 	pos = make_pair(a, b);
 	polarity = p;   
}

pair<int, int> Marker::get_position()
{
	return pos;
}

int Marker::get_polarity()
{
	return polarity;
}

void Marker::flip_polarity()
{
	polarity = 1 - polarity;
}