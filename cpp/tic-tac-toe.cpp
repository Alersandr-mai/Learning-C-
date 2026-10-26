#include <iostream>
#include <vector>
#include <string>

void print_map(const std::vector<std::vector<char>>& map);
bool is_move_correct(const std::vector<std::vector<char>>& map, char cellNumber);
char get_player_cell_number(const std::vector<std::vector<char>>& map);
void make_move(std::vector<std::vector<char>>& map, char cellNumber, bool isZeroNow);
bool has_winner(std::vector<std::vector<char>>& map);

int main()
{
	std::vector<std::vector<char>> map = 
	{
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
	};

	bool isZeroNow = false, isWin = false, isEnd = false;
	int i; char number; std::string s;
	s = "Начать";
	while(s != "Выход")
	{
		std::cout << "Tic-tac-toe\n";
		std::cout << "Играть\n";
		std::cout << "Выход\n";
		std::cout << "Напишите действие\n";
		std::getline(std::cin, s);
		if(s == "Играть")
		{
			std::cout << "\nИгра начинается!\n";
			for(i = 0; i < 9; i++)
			{
				if(isZeroNow == false) std::cout << "Ходят крестики\n";
				else std::cout << "Ходят нолики\n";
		
				print_map(map);
				std::cout << "Введите цифру вашего хода:\n";
				number = get_player_cell_number(map);  
				make_move(map, number, isZeroNow);
				isWin = has_winner(map);
				if(isWin == true)
				{
					print_map(map);
					if(isZeroNow == false) std::cout << "Крестики победили!\n";
					else std::cout << "Нолики победили!\n";
					isEnd = true; break;
				}
				isZeroNow = isZeroNow == false ? true : false;
			}
		if(isEnd == false) {print_map(map); std::cout << "Ничья!\n";}
		std::cout << std::endl;
		}

		else if(s == "Выход") return 0;
		else std::cout << "Неверный ввод. Пожалуйста, введите существующую команду\n\n";
	}
	return 0;
}

//Функция проверки, можно ли поставить в ячейку крестик или нолик
bool is_move_correct(const std::vector<std::vector<char>>& map, char cellNumber)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(map[i][j] == cellNumber) return true;
		}
	}
	return false;
}

//Функция вывода игрового поля
void print_map(const std::vector<std::vector<char>>& map)
{
        for(int i = 0; i < 3; i++)
        {
                for(int j = 0; j < 3; j++)
                {
                        std::cout << map[i][j];
                        if(j == 2) std::cout << std::endl;
                        else std::cout << " ";
                }
        }
        return;
}

//Функция запроса ячейки у пользователя
char get_player_cell_number(const std::vector<std::vector<char>>& map)
{
	while(true)
	{
		std::string s; std::getline(std::cin, s); char c;
		if(s.size() > 1) {std::cout << "Неверный ввод. Пожалуйста, введите цифру от 1 до 9.\n"; continue;}
		else c = s[0];
		if(c >= '1' && c <= '9')
		{
			if(is_move_correct(map, c) == true) return c;
			else {std::cout << "Неверный ввод. Пожалуйста, введите цифру пустой ячейки.\n"; continue;}
		}
		std::cout << "Неверный ввод. Пожалуйста, введите цифру от 1 до 9.\n";
	}
}

//Функция делающая ход
void make_move(std::vector<std::vector<char>>& map, char cellNumber, bool isZeroNow)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(map[i][j] == cellNumber)
			{
				if(isZeroNow == true) map[i][j] = 'O';
				else map[i][j] = 'X';
			}
		}
	}
}

//Функция, определяющаяя наличие победителя
bool has_winner(std::vector<std::vector<char>>& map)
{
	int i, j, cnt = 0;
	for(i = 0; i < 3; i++)
	{
		if(map[i][0] == map[i][1] && map[i][1] == map[i][2]) return true;
		if(map[0][i] == map[1][i] && map[1][i] == map[2][i]) return true;
	}
	if(map[0][0] == map[1][1] && map[1][1] == map[2][2]) return true;
	if(map[2][0] == map[1][1] && map[0][2] == map[1][1]) return true;
	return false;	
}

