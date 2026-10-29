#include "types.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>

/* не знаю как использовать
class Map
{
	private:
	int edge;

	public:
	Map(int edge) 
		: edge(edge)
	{}

};
*/

int sizeToEdge(std::string size)
{
	int lenght, weight;
       	if(size == "XL") {weight = 40; lenght = 80;}
        else if(size == "L") {weight = 30; lenght = 60;}
        else if(size == "S") {weight = 20; lenght = 40;}
        else if(size == "XS") {weight = 10; lenght = 20;}
        else {weight = 20; lenght = 40;}//значение по умолчанию
	return lenght + (weight / 10);
}

std::vector<std::vector<char>> createMap(std::string size, std::mt19937& gen)
{
	int i, j;
	int edge = sizeToEdge(size); int lenght = edge - (edge % 10), weight = (edge % 10) * 10;
	std::cout << weight << " " << lenght << std::endl;
	std::vector<std::vector<char>> map(weight, std::vector<char>(lenght));
	
	/*Заполняем карту травой*/
	for(auto& rows: map)
	{
		for(auto& x: rows)
		{
			x = '#';
		}
	}

	/*Создаём реки*/
	int countRivers = lenght / 20;
	int countRiversInRows = 0;
	for(i = 0; i < weight; i++)
	{
		countRiversInRows = 0;
		for(j = 0; j < lenght; j++)
		{
			if(i > 0 && (map[i-1][j] == '~' || map[i-1][j-1] == '~' || map[i-1][j+1] == '~') 
					&& (map[i][j-1] != '~'))
			{
				if((gen() % 100 < 60 - i) && (countRiversInRows < countRivers)) {map[i][j] = '~'; countRiversInRows++;}
			}	
			
			else if(i == 0)
			{
				if((gen() % 100 < 20) && countRiversInRows < countRivers) {map[i][j] = '~'; countRiversInRows++;}
			}
			
		}
	}

	/*Создаем деревья*/
	for(i = 0; i < weight; i++)
	{
		for(j = 0; j < lenght; j++)
		{
			if((gen() % 100 < 5) && map[i][j] == '#') map[i][j] = '^';
		}
	}

	/*Создаём персонажа*/
	map[weight / 2][lenght / 2] = '@'; 
/*
	for(auto& rows: map)
        {
                for(auto& x: rows)
                {
                        std::cout << x;
                }
                std::cout << std::endl;
        }
*/
	return map;

}

void printMap(std::vector<std::vector<char>> map)
{
	int i, j;
	for(i = 0; i < map.size(); i++)
	{
		for(j = 0; j < map[i].size(); j++)
		{
			if(map[i][j] == '#') std::cout << "\033[32;42m" << map[i][j] << "\033[0m";
			else if(map[i][j] == '~') std::cout << "\033[34;44m" << map[i][j] << "\033[0m";
			else if(map[i][j] == '^') std::cout << "\033[1;33;42m" << map[i][j] << "\033[0m";
			else if(map[i][j] == '@') std::cout << "\033[37;47m" << map[i][j] << "\033[0m";
			if(j == map[i].size() - 1) std::cout << std::endl;
		}
	}
}
