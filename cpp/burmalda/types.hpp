#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>

struct Prices
{
	static constexpr int stones = 10;
};

enum class Color
{
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	PURPLE = 35,
	CIANIC = 36,
	WHITE = 37
};

struct Inventory
{
	int money;
	int stones;
};

class Person
{
	public:
	Person(std::string name, Color c, int hp, Inventory inv) 
		: name(name), c(c), hp(hp), inv(inv) 
	{}
	
	void rename(std::string name)
	{
		this->name = name;
	}

	void getDamage(int damage)
	{
		hp -= damage;
	}

	void sellStones(int count_stones)
	{
		if(inv.stones - count_stones < 0) std::cout << "У вас недостаточно камней\n";
		else
		{
			inv.stones -= count_stones;
			inv.money += count_stones * Prices::stones;
		}
	}

	private:
	std::string name;
	Color c;
	int hp;
	Inventory inv;
};

void printMap(std::vector<std::vector<char>> map);
std::vector<std::vector<char>> createMap(std::string size, std::mt19937& gen);
int sizeToEdge(std::string size);
void makeMove(char c, std::vector<std::vector<char>>& map);
int findPosition(std::vector<std::vector<char>> map);
