#include "Util.h"


int get_board_index(pair<int,int> position)
{
	int radius = position.first;
	int offset = position.second;

	if(radius == 0 && offset == 0)
		return 0;

	return 3*radius*(radius-1)+offset+1;
}

int get_board_index(int radius, int offset)
{
	if(radius == 0 && offset == 0)
		return 0;

	return 3*radius*(radius-1)+offset+1;
}

pair<int, int> get_next_position(pair<int, int> current_position, int direction)
{
	int radius = current_position.first;
	int offset = current_position.second;
	pair<int, int> next_position;

	if(radius == 0)
	{
		next_position.first = 1;
		next_position.second = direction;
		return next_position;	
	}

	int rel_offset = (6*radius + offset - direction*radius)%(6*radius);
	
	int segment;
	if(rel_offset <= radius || rel_offset >= 5*radius)
		segment = 0;
	else if(rel_offset <= 2*radius || rel_offset >= 4*radius)
		segment = 1;
	else
		segment = 2;

	if(segment == 0)
	{
		if( rel_offset >= 5*radius)
		{
			rel_offset += 6;
		}
		radius++;
	}
	else if(segment == 1)
	{
		if( rel_offset >= 4*radius)
		{
			rel_offset++;
		}
		else
			rel_offset--;
	}
	else
	{
		radius--;
		rel_offset -= 3;
	}

	if(radius==0)
	{
		next_position.first = 0;
		next_position.second = 0;
		return next_position;
	}

	offset = (rel_offset + direction*radius)%(6*radius);

	next_position.first = radius;
	next_position.second = offset;

	return next_position;
}

vector<pair<string, pair< int, int> > > fill_moves(string m)
{
	int i=0, j=0;
	string ch = "";
	string temp_str = "";
	vector<pair<string, pair< int, int> > > answer;
	int a,b;
	while(i < m.length())
	{
		int count = 0;
		j = i;
		while(count < 3)
		{
			if(m[j] != ' ')
			{
				while(m[j] != ' ')
					j++;
				count++;
			}
			while(m[j] == ' ')
				j++;
		}
		temp_str = m.substr(i, j - i);
		i = j;
		if(fill_move(temp_str, ch, a, b) == 1)
		{
			answer.push_back(make_pair(ch, make_pair(a, b)));
		}
		else
		{
			break;
		}
	}
	return answer;
}

int fill_move(string m, string &ch, int &a, int &b)
{
	if(m.length() == 0)
		return 0;
	
	int i=0;
	while(m[i]==' ')
		i++;

	int j=i;
	while(m[j]!=' ')
		j++;
	ch = m.substr(i, j-i);

	i = j;
	while(m[i]==' ')
		i++;

	j=i;
	while(m[j]!=' ')
		j++;

	a = stoi(m.substr(i, j-i));

	i = j+1;
	j++;
	while(j<m.length() && m[j]!=' ')
		j++;

	if(j == m.length() - 1)
	{
		b = stoi(m.substr(i, j-i+1));
	}
	else
	{
		b = stoi(m.substr(i, j-i));
	}
	return 1;
}