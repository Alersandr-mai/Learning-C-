#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "inventory.hpp"
#include "weapon.hpp"

class Hero{
	private:
		std::string name;
		int level;
		int choice_class;
		int hp; 
		std::vector<int> coordinate;
		Inventory inventory;
		Weapon* weapon;
	public:
		Hero(std::string name = "Безымянный", int level = 1, int hp = 100, std::vector<int> coordinate = {2, 0});

		void rename();

		void printProfile() const;

		void moveCoordinate(char c);
		void giveCoordinate(int x, int y);
		std::vector<int> xAndy();

		Inventory& getInventory();

		void equipItem(Item* item);
};
		
