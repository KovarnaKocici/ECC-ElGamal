#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

void clean()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool input_user(int &el)
{
	cin >> el; //читаємо
	if (!cin) //перевіряємо помилку
	{
		clean(); //відновлюємо працездатність потоку і скидаємо залишок
		throw invalid_argument("\n Was inputted inacceptable value\n\n");
	}
	clean(); //скидаємо залишок
	return 1;
}
