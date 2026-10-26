#pragma once

#include <iostream>
#include <string>


class Item{
	private:
		int id;
		std::string name;

	protected:
		int count;

	public:
		Item(int id = 0, std::string name = "Вещь", int count = 1);

		virtual std::string getName() const;
		virtual int getType() const;
};
/*
class Equip{
	protected:
		int durability;

	public:
		Equip(int durability = 1);

		bool isBroken() const;
};

class Weapon : public Loot, public Equip{
	private:
		double damage;

	public:
		Weapon(std::string name = "Оружие", double damage = 1, int durabiliy = 1);
		
};

class Armor : public Loot, public Equip{
	private:
		double defense;

	public:
		Armor(std::string name = "Броня", double defense = 1, int durability = 1);
};
*/
