#include <iostream>
#include <string>
int main()
{
	int len = 0; std::string stat = "Ожидание";
	std::string s; std::getline(std::cin, s);
	while(s != "Конец рабочего дня")
	{
		if(s == "Новый клиент") ++len;
		else if(s == "Длина очереди") std::cout << "Длина очереди: " << len << std::endl;
		else if(s == "Начало обслуживания") 
		{
			if(stat == "Обслуживание") std::cout << "Обслуживание не начато, не завершено обслуживание предыдущего клиента\n";
			else if(len == 0) std::cout << "Обслуживание не начато, в очереди никого нет\n";
			else {--len; stat = "Обслуживание";}
		}
		else if(s == "Текущий статус") std::cout << "Текущий статус: " << stat << std::endl;
		else if(s == "Завершение обслуживания") stat = "Ожидание";
		else std::cout << "Неизвестная команда\n";
		std::getline(std::cin, s);
	}
	std::cout << "Конец рабочего дня\n";
	return 0;
}

