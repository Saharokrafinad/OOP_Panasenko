#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
using namespace std;
// Вывод сообщений об ошибках
//----------------------------------------------------------------------------------------------
class ExceptionHelper
{
public:
	static void PrintMsg(string message);
};
//----------------------------------------------------------------------------------------------
// Геометрическая фигура
//----------------------------------------------------------------------------------------------
class Shape
{
private:
	int density;
protected:
	Shape() {};
public:
	static Shape* In(ifstream& ifst);
	virtual void InData(ifstream& ifst) = 0;
	virtual void OutData(ofstream& ofst) = 0;
	virtual int Perimeter() = 0;
	bool Compare(Shape& other);
	virtual void OutRectangles(ofstream& ofst);
};
//----------------------------------------------------------------------------------------------
// Прямоугольник
//----------------------------------------------------------------------------------------------
class Rectangle : public Shape
{
private:
	int x, y;
public:
	void InData(ifstream& ifst);
	void OutData(ofstream& ofst);
	void OutRectangles(ofstream& ofst);
	int Perimeter();
	Rectangle() {};
};
//----------------------------------------------------------------------------------------------
// Круг
//----------------------------------------------------------------------------------------------
class Circle : public Shape
{
private:
	int r;
public:
	void InData(ifstream& ifst);
	void OutData(ofstream& ofst);
	int Perimeter();
	Circle() {};
};
//----------------------------------------------------------------------------------------------
// Треугольник
//----------------------------------------------------------------------------------------------
class Triangle : public Shape
{
private:
	int x1, x2, x3;
public:
	void InData(ifstream& ifst);
	void OutData(ofstream& ofst);
	int Perimeter();
	Triangle() {};
};

//----------------------------------------------------------------------------------------------
// Элемент контейнера - односвязного списка
//----------------------------------------------------------------------------------------------
class Node
{
public:
	Shape* data;
	Node* next;
};
//----------------------------------------------------------------------------------------------
// Контейнер - односвязный список
//----------------------------------------------------------------------------------------------
class Container
{
private:
	Node* head;
	Node* last;
public:
	Container() { head = NULL; last = NULL; }
	void InitContainer();
	void InContainer(ifstream& ifst);
	void OutContainer(ofstream& ofst);
	void ClearContainer();
	void OutRectangles(ofstream& ofst);
	void Sort();
	~Container() { ClearContainer(); }
};
#endif