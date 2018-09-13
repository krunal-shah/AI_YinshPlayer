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

	//radius change
	int axis = (direction+3)%3;
	int rel_offset = (6*radius + offset - direction*radius)%(6*radius);
	int segment = rel_offset > 3*radius ? (6 + (rel_offset + 1)/radius )%6 : (6 + (rel_offset - 1)/radius )%6;

	if( segment == 0 || segment == 5 )
		radius++;
	if( segment == 2 || segment == 3 )
		radius--;

	//offset change
	if( segment == 1 )
		rel_offset--;
	else if (segment == 4)
		rel_offset++;
	else
	{
		if (segment == 2 || segment == 3)
		{
			rel_offset -= 3;
		}
		else if (segment == 5)
		{
			rel_offset += 6;
		}
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