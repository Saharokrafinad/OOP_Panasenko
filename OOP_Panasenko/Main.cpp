﻿#include <iostream>
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
	if (!inFileStream.is_open())
	{
		ExceptionHelper::PrintMsg("Невозможно открыть входной файл, в директории нет файла с именем: " + (string)argv[1]);
	}
	ofstream outFileStream(argv[2]);
	Container c;

	cout << "Старт" << endl;
	c.InContainer(inFileStream);
	cout << "Контейнер заполнен" << endl;
	cout << "Контейнер отсортирован" << endl;
	c.Sort();
	c.OutContainer(outFileStream);
	c.OutRectangles(outFileStream);
	c.ClearContainer();
	cout << "Контейнер очищен" << endl;
	cout << "Завершение работы" << endl;

	system("pause");
	return 0;
}