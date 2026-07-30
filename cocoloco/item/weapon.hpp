#pragma once

#include "item.hpp"

#include <iostream>

class Weapon : public Item{
	private:
		double damage;

	public:
		Weapon(int id = 100, std::string name = "Оружие", int count = 1, double damage = 1);

		virtual double strike() const;

		int getType() const override;
};

class Sword : public Weapon{
	public:
		Sword(int id = 100, std::string name = "Меч", int count = 1, double damage = 5);

		static Sword* createWoodenSword();
		static Sword* createSteelSword();
		static Sword* createMegaSuperDuperSword();
		
};

