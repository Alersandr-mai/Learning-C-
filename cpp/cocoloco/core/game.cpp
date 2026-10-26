#include "game.hpp"

Game::Game(bool isRunning, int length, int weight, Map* gameMap)
	: isRunning(true), lenght(0), weight(0), gameMap(nullptr)
{}

void Game::start()
{
	/*std::cout << "Введите длину карты(1 - 40): ";
	std::cin >> lenght;
	std::cout << "Введите ширину карты(1 - 40): ";
	std::cin >> weight;*/
	lenght = 60, weight = 30;
	if(gameMap != nullptr) delete gameMap;
	gameMap = new Map(lenght, weight);
	gameMap->generateMap(lenght, weight);
	hero.giveCoordinate(weight / 2, lenght / 2);

	hero.getInventory().putThing(Sword::createWoodenSword());
	std::cout << "Игра началась!\n";
}

void Game::run()
{
	start();

	char c;
	while(isRunning && std::cin >> c)
	{
		std::cout << "\033[2J\033[H";
		processInput(c);
	}
}

void Game::processInput(char c)
{
	if(c == 'p'){
		hero.printProfile();
		while(std::cin >> c && c != 'q'){
			std::cout << "\033[2J\033[H";	
			if(c == 'r'){
		       		hero.rename();
				hero.printProfile();
			}
			else NotExist();
		}
	}

	else if(c == 'm' && gameMap != nullptr){
		gameMap->printMap();
		while(std::cin >> c && c != 'q'){
			std::cout << "\033[2J\033[H";
			if(c == 'w' || c == 's' || c == 'a' || c == 'd' || c == 'e'){
				move(c);
				gameMap->printMap();

				if(c == 'e') workWithInventory(c);
			}
			else
				NotExist();
		}
	}

	else if(c == 'e') workWithInventory(c);

	else NotExist();
}

void Game::NotExist()
{
	std::cout << "Такой команды не существует :(\n";
}

void Game::move(char c)
{
	bool isChest = false;
	std::vector<int> coor = hero.xAndy();
	if(c == 'w'){
		if(gameMap->isWalkable(coor[0] + 1, coor[1])){
			if(gameMap->getTitle(coor[0] + 1, coor[1]) == '+') isChest = true;
			gameMap->setTitle(coor[0] + 1, coor[1], '@');
			gameMap->setTitle(coor[0], coor[1], '#');
			hero.moveCoordinate(c);

			workWithChest(isChest, c);
		}
	}


	else if(c == 's'){
		if(gameMap->isWalkable(coor[0] - 1, coor[1])){
			if(gameMap->getTitle(coor[0] - 1, coor[1]) == '+') isChest = true;
			gameMap->setTitle(coor[0] - 1, coor[1], '@');
			gameMap->setTitle(coor[0], coor[1], '#');
			hero.moveCoordinate(c);

			workWithChest(isChest, c);
		}
	}

	else if(c == 'a'){
		if(gameMap->isWalkable(coor[0], coor[1] - 1)){
			if(gameMap->getTitle(coor[0], coor[1] - 1) == '+') isChest = true;
			gameMap->setTitle(coor[0], coor[1] - 1, '@');
			gameMap->setTitle(coor[0], coor[1], '#');
			hero.moveCoordinate(c);

			workWithChest(isChest, c);
		}
	}

	else if(c == 'd'){
		if(gameMap->isWalkable(coor[0], coor[1] + 1)){
			if(gameMap->getTitle(coor[0], coor[1] + 1) == '+') isChest = true;
			gameMap->setTitle(coor[0], coor[1] + 1, '@');
			gameMap->setTitle(coor[0], coor[1], '#');
			hero.moveCoordinate(c);

			workWithChest(isChest, c);
		}
	}
}

void Game::workWithChest(bool isChest, char c){
	if(isChest == true){
		Chest chest;
        	chest.openChest();

       		while(std::cin >> c && c != 'q'){
                	int num = c - '0';
                	if(num > 0 && num <= 9){
                        	hero.getInventory().giveFromOneToTwo(chest.getInventory(), num);
                        	chest.openChest();
               		}

                	else{
                       		NotExist();
               		}
     		}
	}
}

void Game::workWithInventory(char c){
	hero.getInventory().printInventory();
	while(std::cin >> c && c != 'q'){
		int num = c - '0';
		Item* item = hero.getInventory().getCell(num);
		if(item == nullptr){
			std::cout << "В инвентаре нет предмета на такой позиции\n";
			return;
		}

		std::cout << item->getName() << "\n";
		std::cout << "Выберете, что хотите сделать:\n";
		std::cout << "Удалить предмет(r)\n";
		std::cout << "Экипировать предмет(c)\n";

		std::cin >> c;
		if(c == 'r'){
			hero.getInventory().removeItem(num);
			hero.getInventory().printInventory();
		}

		else if(c == 'c'){
			int type = item->getType();
			if(type == 1){
				hero.equipItem(item);
			}
		}
	}
}
Game::~Game(){
	delete gameMap;
}
