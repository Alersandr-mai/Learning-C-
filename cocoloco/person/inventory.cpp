#include "inventory.hpp"

Inventory::Inventory(int capacity)
	: capacity(capacity)
{
	inventory.reserve(capacity);
}

void Inventory::increaseCapacity(){
	inventory.reserve(capacity + 3);
	capacity += 3;
}

void Inventory::putThing(Item* thing){
	if(inventory.size() < this->capacity){
		inventory.push_back(thing);
	}
	else
		std::cout << "В инвентаре нет свободного метса\n";
}

void Inventory::printInventory() const{
	for(int i = 0; i < inventory.size(); i++){
		if(inventory[i] != nullptr){
			std::string name = inventory[i]->getName();
			std::cout << i + 1 << " " << name << "\n";
		}
	}
	//std::cout << inventory.size() << "\n";
}

void Inventory::giveFromOneToTwo(Inventory& from, int number){
	if(number < 1 || number > from.inventory.size()){
		std::cout << "В сундуке нет предмета с таким номером\n";
		return;
	}
	
	Item* choice = from.inventory[number - 1];
	if(choice == nullptr){
		std::cout << "Пустой слот\n";
		return;
	}

	if(inventory.size() >= capacity){
		std::cout << "Инвентарь полон! Вы не можете взять предмет\n";
		return;
	}

	from.inventory.erase(from.inventory.begin() + number - 1);

	inventory.push_back(choice);
}

Item* Inventory::getCell(int number){
	if(number > 0 && number <= inventory.size())
		return inventory[number - 1];
	else
		return nullptr;
}

bool Inventory::isEmpty() const{
	return inventory.empty();
}

void Inventory::removeItem(int number){
	Item* item = getCell(number);
	if(item == nullptr){
		std::cout << "В инвентаре нет предмета под таким номером\n";
		return;
	}

	inventory.erase(inventory.begin() + number - 1);
}

Inventory::~Inventory(){
	for(auto& i: inventory) delete i;
}
