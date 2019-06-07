#include "Program.h"
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------
// ����� ��������� �� �������
//----------------------------------------------------------------------------------------------
void ExceptionHelper::PrintMsg(string message)
{
	cout << message << endl;
	system("pause");
	exit(EXIT_FAILURE);
}
//----------------------------------------------------------------------------------------------
// �������������� ������
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
			throw exception("�� ������� ����� ������������ ������������ ������! ������ ��������� ����������.");
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
			throw exception("��������� �� ����� ���� ������ 0! ������ ��������� ����������.");
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());;
	}
}
void Shape::OutData(ofstream& ofst)
{
	ofst << " ��������� = " << density;
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
// �������������
//----------------------------------------------------------------------------------------------
void Rectangle::InData(ifstream& ifst)
{
	try
	{
		ifst >> x >> y;
		if (x <= 0 || y <= 0)
			throw exception("������� �������������� ������ ���� ��������������! ������ ��������� ����������.");

		Shape::InData(ifst);
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}
void Rectangle::OutData(ofstream& ofst)
{
	ofst << "�������������: x = " << x << ", y = " << y;
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
// ����
//----------------------------------------------------------------------------------------------
void Circle::InData(ifstream& ifst)
{
	try
	{
		ifst >> r;
		if (r <= 0)
			throw exception("������ ����� ������ ���� �������������! ������ ��������� ����������.");

		Shape::InData(ifst);
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}

void Circle::OutData(ofstream& ofst)
{
	ofst << "����: r = " << r;
	Shape::OutData(ofst);
}
int Circle::Perimeter()
{
	return int(2 * 3.14 * r);
}
//----------------------------------------------------------------------------------------------
// �����������
//----------------------------------------------------------------------------------------------
void Triangle::InData(ifstream& ifst)
{
	try
	{
		ifst >> x1 >> x2 >> x3;
		if (x1 <= 0 || x2 <= 0 || x3 <= 0)
			throw exception("������� ������������ ������ ���� ��������������! ������ ��������� ����������.");

		Shape::InData(ifst);
	}
	catch (exception& except)
	{
		ExceptionHelper::PrintMsg(except.what());
	}
}
void Triangle::OutData(ofstream& ofst)
{
	ofst << "�����������: x1 = " << x1 << ", x2 = " << x2 << ", x3 = " << x3;
	Shape::OutData(ofst);
}
int Triangle::Perimeter()
{
	return int(x1 + x2 + x3);
}
//----------------------------------------------------------------------------------------------
// ��������� - ����������� ������
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
	ofst << "��������� ��������:\n" << endl;
	Node* current = head;
	if (current == NULL)
		return;
	while (current != NULL)
	{
		current->data->OutData(ofst);
		ofst << " �������� = " << current->data->Perimeter() << endl;
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
	ofst << "\n������ ��������������:" << endl;
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