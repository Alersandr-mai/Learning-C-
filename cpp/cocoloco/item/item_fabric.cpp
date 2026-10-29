#include "item_fabric.hpp"

Item* createItemById(int id){
	switch(id){
		case 101: return Sword::createWoodenSword();
		case 102: return Sword::createSteelSword();
		case 199: return Sword::createMegaSuperDuperSword();
	
		default: return nullptr;
	}
}

