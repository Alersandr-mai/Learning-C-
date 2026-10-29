#include "person.hpp"

Hero::Hero(std::string name, int level, int hp, std::vector<int> coordinate)
                        : name(name), level(level), hp(hp), coordinate(coordinate), inventory(9)
				{/*
                        		std::cout << "Ваш персонаж создался!\n";
                        		std::cout << "Если хотите дать ему имя, то зайдите в профиль\n";
                		*/}

void Hero::rename()
{
        std::cout << "Введите новое имя для своего персонажа:\n";
        std::cin >> name;
}

void Hero::printProfile() const
{
	std::cout << "=====================================\n";
        std::cout << "Имя: " << name << "\n";
        std::cout << "Уровень: " << level << "\n";
        std::cout << "Здоровье: " << hp << "\n";
        std::cout << "\n";
        std::cout << "если хотите переименовать своего персонажа, нажмите r\n";
        std::cout << "=====================================" << "\n";
}

std::vector<int> Hero::xAndy()
{
	std::vector<int> coor = std::vector<int>(2);
	coor[0] = coordinate[0];
	coor[1] = coordinate[1];
	return coor;
}

void Hero::moveCoordinate(char c)
{
	if(c == 'w')
		coordinate[0] += 1;
	
	else if(c == 's')
		coordinate[0] -= 1;

	else if(c == 'a')
		coordinate[1] -= 1;

	else if(c == 'd')
		coordinate[1] += 1;
}

void Hero::giveCoordinate(int x, int y)
{
	coordinate[0] = x;
	coordinate[1] = y;
}

Inventory& Hero::getInventory(){
	return inventory;
}

void Hero::equipItem(Item* item){
	if(item->getType() == 1){
		this->weapon = dynamic_cast<Weapon*>(item);
		std::cout << item->getName() << " успешно экипирован\n";
	}
}
