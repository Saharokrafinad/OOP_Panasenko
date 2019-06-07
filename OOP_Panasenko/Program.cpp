#include "Program.h"
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------
// Вывод сообщений об ошибках
//----------------------------------------------------------------------------------------------
void ExceptionHelper::PrintMsg(string message)
{
	cout << message << endl;
	system("pause");
	exit(EXIT_FAILURE);
}
//----------------------------------------------------------------------------------------------
// Геометрическая фигура
//----------------------------------------------------------------------------------------------
Shape* Shape::In(ifstream& ifst)
{
	Shape* sp = NULL;
	int k;
	ifst >> k;

	try
	{
		switch (k)
		{
		case 1:
			sp = new Rectangle;
			break;
		case 2:
			sp = new Circle;
			break;
		case 3:
			sp = new Triangle;
			break;
		default:
			throw exception("Во входном файле присутствует неопознанная фигура! Работа программы прекращена.");
		}
		sp->InData(ifst);
		return sp;
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}
void Shape::InData(ifstream& ifst)
{
	try
	{
		ifst >> density;
		if (density < 0)
			throw exception("Плотность не может быть меньше 0! Работа программы прекращена.");
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());;
	}
}
void Shape::OutData(ofstream& ofst)
{
	ofst << " Плотность = " << density;
}
bool Shape::Compare(Shape& other)
{
	return Perimeter() < other.Perimeter();
}
void Shape::OutRectangles(ofstream& ofst)
{
	ofst << "";
}
//----------------------------------------------------------------------------------------------
// Прямоугольник
//----------------------------------------------------------------------------------------------
void Rectangle::InData(ifstream& ifst)
{
	try
	{
		ifst >> x >> y;
		if (x <= 0 || y <= 0)
			throw exception("Стороны прямоугольника должны быть положительными! Работа программы прекращена.");

		Shape::InData(ifst);
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}
void Rectangle::OutData(ofstream& ofst)
{
	ofst << "Прямоугольник: x = " << x << ", y = " << y;
	Shape::OutData(ofst);
}
int Rectangle::Perimeter() 
{ 
	return 2 * (x + y); 
}
void Rectangle::OutRectangles(ofstream& ofst)
{
	OutData(ofst);
}
//----------------------------------------------------------------------------------------------
// Круг
//----------------------------------------------------------------------------------------------
void Circle::InData(ifstream& ifst)
{
	try
	{
		ifst >> r;
		if (r <= 0)
			throw exception("Радиус круга должен быть положительным! Работа программы прекращена.");

		Shape::InData(ifst);
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}

void Circle::OutData(ofstream& ofst)
{
	ofst << "Круг: r = " << r;
	Shape::OutData(ofst);
}
int Circle::Perimeter()
{
	return int(2 * 3.14 * r);
}
//----------------------------------------------------------------------------------------------
// Треугольник
//----------------------------------------------------------------------------------------------
void Triangle::InData(ifstream& ifst)
{
	try
	{
		ifst >> x1 >> x2 >> x3;
		if (x1 <= 0 || x2 <= 0 || x3 <= 0)
			throw exception("Стороны треугольника должны быть положительными! Работа программы прекращена.");

		Shape::InData(ifst);
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}
void Triangle::OutData(ofstream& ofst)
{
	ofst << "Треугольник: x1 = " << x1 << ", x2 = " << x2 << ", x3 = " << x3;
	Shape::OutData(ofst);
}
int Triangle::Perimeter()
{
	return int(x1 + x2 + x3);
}
//----------------------------------------------------------------------------------------------
// Контейнер - односвязный список
//----------------------------------------------------------------------------------------------
void Container::InitContainer()
{
	head = NULL;
	last = NULL;
}
void Container::InContainer(ifstream& ifst)
{
	while (!ifst.eof())
	{
		Node* temp = new Node;
		Shape* data = Shape::In(ifst);
		temp->data = data;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			last = temp;
		}
		else
		{
			last->next = temp;
			last = temp;
		}
	}
}
void Container::OutContainer(ofstream& ofst)
{
	ofst << "Контейнер содержит:\n" << endl;
	Node* current = head;
	if (current == NULL)
		return;
	while (current != NULL)
	{
		current->data->OutData(ofst);
		ofst << " Периметр = " << current->data->Perimeter() << endl;
		current = current->next;
	}
}
void Container::ClearContainer()
{
	while (head != NULL)
	{
		Node* forDelete = head;
		head = head->next;
		delete forDelete;
	}
}
void Container::OutRectangles(ofstream& ofst)
{
	ofst << "\nТолько прямоугольники:" << endl;
	Node* current = head;
	if (current == NULL)
		return;
	while (current != NULL)
	{
		current->data->OutRectangles(ofst);
		current = current->next;
		ofst << endl;

	}
}

void Container::Sort()
{
	for (Node* i = head; i; i = i->next)
		for (Node* j = head; j; j = j->next)
			if (i->data->Compare(*(j->data)))
				swap(i->data, j->data);
}