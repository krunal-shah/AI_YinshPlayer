#include "Marker.h"

Marker::Marker(int a, int b, int polarity)
{
 	a = a;
 	b = b;
 	polarity = polarity;   
}

pair<int, int> Marker::get_position()
{
	return pos;
}

int Marker::get_polarity()
{
	return polarity;
}

string Marker::my_type()
{
	return "marker";
}