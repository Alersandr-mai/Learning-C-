#pragma once

#include "title.hpp"

#include <iostream>
#include <vector>
#include <random>

class Map{
	private:
		int lenght;
		int weight;
		std::vector<std::vector<char>> map;	
	public:
		Map(int lenght, int weight);

		void generateMap(int lenght, int weight);
		void printMap() const;
		bool isWalkable(int x, int y) const;
		void setTitle(int x, int y, char c);
		char getTitle(int x, int y);
		/*void getParametr(int& par);*/
};
