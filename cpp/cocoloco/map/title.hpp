#pragma once

#include "inventory.hpp"
#include "item_fabric.hpp"

#include <iostream>
#include <random>


class Chest{
	private:
		Inventory inventory;

	public:
		Chest();

		void generateChest();
		void openChest() const;
		Inventory& getInventory();
};

