#include "title.hpp"

Chest::Chest()
	: inventory(1)
{
	std::cout << "Вы открыли сундук!\n";
	generateChest();
}

void Chest::generateChest(){
	std::random_device seed;
	std::mt19937 gen(seed());

	//на потом(количество лута в сундуке)
	//std::uniform_int_distribution<int> distCount(1, 6);

	//пока что сундук на 1 место

	std::uniform_int_distribution<int> idSword(101, 102);

	Item* loot1 = createItemById(idSword(gen));
	inventory.putThing(loot1);
}

void Chest::openChest() const{
	inventory.printInventory();
	if(inventory.isEmpty()){
		std::cout << "Сундук пуст\n";
	}
}

Inventory& Chest::getInventory(){
	return inventory;
}
