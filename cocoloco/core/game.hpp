#pragma once

#include <iostream>
#include <string>
#include "person.hpp"

#include "map.hpp"
#include "title.hpp"

#include "item.hpp"
#include "weapon.hpp"

class Game{
	private:
		bool isRunning;
		Hero hero;
		Map* gameMap;
		int lenght, weight;

	public:
		Game(bool isRunning = true, int lenght = 0, int weight = 0, Map* gameMap = nullptr);

		~Game();

		void start();

		void processInput(char c);

		void printProfile();

		void run();

		void NotExist();

		void move(char c);
		void workWithChest(bool isChest, char c);
		void workWithInventory(char c);

};

