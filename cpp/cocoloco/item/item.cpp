#include "item.hpp"

Item::Item(int id, std::string name, int count) 
	: id(id), name(name), count(count)
{}

std::string Item::getName() const{
	return name;
}

int Item::getType() const{
	return 0;
}
/*
Equip::Equip(int durability)
	: durability(durability)
{}

bool Equip::isBroken() const{
	if(durability <= 0) return true;
	else return false;
}


Weapon::Weapon(std::string name, double damage, int durability)
	: Loot(name, count), Equip(durability), damage(damage)
{}




Armor::Armor(std::string name, double defense, int durability)
	: Loot(name, count), Equip(durability), defense(defense)
{}
*/
