#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
using namespace std;
//----------------------------------------------------------------------------------------------
// �������������� ������
//----------------------------------------------------------------------------------------------
class Shape
{
public:
	int density;
	static Shape* In(ifstream& ifst);
	virtual void InData(ifstream& ifst) = 0;
	virtual void OutData(ofstream& ofst) = 0;
	virtual int Perimeter() = 0;
	bool Compare(Shape& other);
	virtual void OutRectangles(ofstream& ofst);
};
//----------------------------------------------------------------------------------------------
// �������������
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
	Rectangle(int x, int y, int density);
	~Rectangle() {};
};
//----------------------------------------------------------------------------------------------
// ����
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
	Circle(int r, int density);
	~Circle() {};
};
//----------------------------------------------------------------------------------------------
// �����������
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
	Triangle(int x1, int x2, int x3, int density);
	~Triangle() {};
};

//----------------------------------------------------------------------------------------------
// ������� ���������� - ������������ ������
//----------------------------------------------------------------------------------------------
class Node
{
public:
	Shape* data;
	Node* next;
	Node(Shape* data, Node* next);
};
//----------------------------------------------------------------------------------------------
// ��������� - ����������� ������
//----------------------------------------------------------------------------------------------
class Container
{
public:
	Node * head;
	Node* last;
	Container() { head = NULL; last = NULL; }
	void InitContainer();
	void InContainer(ifstream& ifst);
	void OutContainer(ofstream& ofst);
	void ClearContainer();
	void OutRectangles(ofstream& ofst);
	void Sort();
	void Add(Shape* shape);
	~Container() { ClearContainer(); }
};
#endif