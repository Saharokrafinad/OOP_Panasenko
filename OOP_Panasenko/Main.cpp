#include <iostream>
#include "Program.h"
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 3)
	{
		cout << "Не найдены файлы in_file out_file" << endl;
		system("pause");
		exit(1);
	}

	ifstream inFileStream(argv[1]);
	ofstream outFileStream(argv[2]);
	Container container;

	cout << "Старт" << endl;
	container.InContainer(inFileStream);
	cout << "Контейнер заполнен" << endl;
	cout << "Контейнер отсортирован" << endl;
	container.Sort();
	container.OutContainer(outFileStream);
	container.OutRectangles(outFileStream);
	container.ClearContainer();
	cout << "Контейнер очищен" << endl;
	cout << "Завершение работы" << endl;

	system("pause");
	return 0;
}