#include "types.hpp"
#include <iostream>

void makeMove(char c, std::vector<std::vector<char>>& map)
{
	bool isMove = false;
	int pos = findPosition(map);
	int i = pos / 100, j = pos % 100;
	int weight = map.size(), lenght = map[0].size();
	if(c == 'a')
	{
		if((j > 0) && (map[i][j - 1] == '#')) {map[i][j - 1] = '@'; isMove = true;}
	}
	else if(c == 'd')
	{
		if((j < lenght - 1) && (map[i][j + 1] == '#')) {map[i][j + 1] = '@'; isMove = true;}
	}
	else if(c == 's')
	{
		if((i < weight - 1) && (map[i + 1][j] == '#')) {map[i + 1][j] = '@'; isMove = true;}
	}
	else if(c == 'w')
	{
		if((i > 0) && (map[i - 1][j] == '#')) {map[i - 1][j] = '@'; isMove = true;}
	}
	else map[i][j] = '@';
	if(isMove == false) {std::cout << "Вы не можете сделать этот ход!\n";}
	else map[i][j] = '#';
}

int findPosition(std::vector<std::vector<char>> map)
{
	int i, j;
	for(i = 0; i < map.size(); i++)
	{
		for(j = 0; j < map[i].size(); j++)
		{
			if(map[i][j] == '@') return i * 100 + j;
		}
	}

	return -1;
}
