#include "weapon.hpp"

Weapon::Weapon(int id, std::string name, int count, double damage)
	: Item(id, name, count), damage(damage)
{}

double Weapon::strike() const{
	return damage;
}

int Weapon::getType() const{
	return 1;
}

Sword::Sword(int id, std::string name, int count, double damage)
	: Weapon(id, name, count, damage)
{}

Sword* Sword::createWoodenSword(){
	return new Sword(101, "Деревянный меч", 1, 5);
}
Sword* Sword::createSteelSword(){
	return new Sword(102, "Стальной меч", 1, 15);
}

Sword* Sword::createMegaSuperDuperSword(){
	std::cout  << "Вы заполучили Мега-Супер-Дупер меч\n";
	return new Sword(199, "Мега-Супер-Дупер Меч", 1, 200);
}
