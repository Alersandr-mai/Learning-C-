#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "item.hpp"

class Inventory{
	private:
		std::vector<Item*> inventory;
		int capacity;

	public:
		Inventory(int capacity = 9);

		~Inventory();

		void increaseCapacity();

		void putThing(Item* thing);

		void printInventory() const;
		Item* getCell(int number);
		void giveFromOneToTwo(Inventory& from, int number);

		bool isEmpty() const;

		void removeItem(int number);
};

