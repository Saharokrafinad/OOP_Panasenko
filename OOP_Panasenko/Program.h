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
	Shape() {};
	static Shape* In(ifstream& ifst);
	virtual void InData(ifstream& ifst) = 0;
	virtual void OutData(ofstream& ofst) = 0;
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
	Rectangle() {};
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
	Circle() {};
};
//----------------------------------------------------------------------------------------------
// ������� ���������� - ������������ ������
//----------------------------------------------------------------------------------------------
class Node
{
public:
	Shape* data;
	Node* next;
};
//----------------------------------------------------------------------------------------------
// ��������� - ����������� ������
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
	~Container() { ClearContainer(); }
};
#endif