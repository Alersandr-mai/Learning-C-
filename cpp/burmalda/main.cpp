#include "types.hpp"

int main()
{
	std::random_device seed;
	std::mt19937 gen(seed());
	
	std::string size;
	std::cout << "Введите размер карты(XL/L/S/XS): ";
	std::cin >> size;
	std::cout << std::endl;

	char c;
	std::vector<std::vector<char>> map;
        map = createMap(size, gen);
	printMap(map);
	while(std::cin >> c)
	{
		makeMove(c, map);
		std::cout << "\033[2J\033[H";
		printMap(map);
	}
	return 0;
}
