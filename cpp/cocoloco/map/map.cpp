#include "map.hpp"

Map::Map(int lenght, int weight)
	{}

void Map::generateMap(int lenght, int weight)
{
	this->lenght = lenght;
	this->weight = weight;
	map = std::vector<std::vector<char>>(weight, std::vector<char>(lenght));
	
	/*Генерация травы*/
	for(auto& rows: map)
        {
        	for(auto& x: rows) x = '#';
        }

	std::random_device seed;
        std::mt19937 gen(seed());

	/*Генерация деревьев*/
	for(auto& rows: map){
		for(auto& x: rows)
		{
			if(gen() % 100 <= 5) x = '^';
		}
	}

	/*Генерация сундуков*/
	int maxCount = 20, count = 0;
	for(auto& rows: map){
		int countRow = 0;
		for(auto& x: rows){
			if(gen() % 100 <= 3 && countRow == 0 && count < maxCount ){
				x = '+'; 
				count++;
				countRow++;
			}
		}
	}

	map[weight/2][lenght/2] = '@';
}

void Map::printMap() const
{
	std::cout << "\033[2J\033[H";
	for(int i = weight - 1; i >= 0; i--){
		for(int j = 0; j < lenght; j++) {
			if(map[i][j] == '#')
				std::cout << "\033[1;32;42m" << map[i][j] << "\033[0m";
			if(map[i][j] == '^')
				std::cout << "\033[33;43m" << map[i][j] << "\033[0m";
			if(map[i][j] == '@')
				std::cout << "\033[37;47m" << map[i][j] << "\033[0m";
			if(map[i][j] == '+') 
				std::cout << "\033[30;42m" << map[i][j] << "\033[0m";
		}
		std::cout << "\n";
	}
}
/*
void Map::getParametr(int& par)
{
	bool isTrue = false;
	while(!isTrue){
		std::cin >> par;
		if(par > 0 && par <= 40) isTrue = true;
		else std::cout << "Введено неверное значение\n";
	}
}
*/
bool Map::isWalkable(int x, int y) const
{
	if(map[x][y] == '#' || map[x][y] == '+') return true;
	else return false;
}

void Map::setTitle(int x, int y, char c)
{
	if(c == '#') map[x][y] = '#';
	if(c == '@') map[x][y] = '@';
}

char Map::getTitle(int x, int y){
	return map[x][y];
}
