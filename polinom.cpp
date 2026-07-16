# include <iostream>
#include <fstream>
const int MAXLEN = 100;
const char* FNAME = "TEST1.txt";
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	int bw = 0;
	int ew = 0;
	char str[MAXLEN];
	int count = 0;
	int maxlen = 0;
	int k = 0;
	ifstream file;
	file.open(FNAME);
	file.getline(str, MAXLEN);
	int i = 0;
	cout << str << endl;

	while (str[i] != '\0')
	{
		while (str[i] != '\0' and str[i] == ' ')
		{
			i++;
		}
		bw = i;
		cout << "bw= " << bw << endl;
		while (str[i] != '\0' and str[i] != ' ')
		{
			i++;
		}
		ew = i - 1;

		cout << "ew= " << ew << endl;
		count = ew - bw;
		int j = 0;
		int start = bw;
		while (start < ew)
		{
			if (str[bw + j] == str[ew - j])
			{
				k++;

			}
			start++;
		}
		if (k == count)
		{
			maxlen = count;
		}
		if (k > 0)
		{
			cout << maxlen + 1 << endl;
		}
		else
		{
			cout << "Полинома нет" << endl;
		}
		k = 0;

	}


}