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
	cin >> el; //������
	if (!cin) //���������� �������
	{
		clean(); //���������� ������������� ������ � ������� �������
		throw invalid_argument("\n Was inputted inacceptable value\n\n");
	}
	clean(); //������� �������
	return 1;
}
