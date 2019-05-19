#include "Program.h"
//----------------------------------------------------------------------------------------------
// �������������� ������
//----------------------------------------------------------------------------------------------
Shape* Shape::In(ifstream& ifst)
{
	Shape* sp = NULL;
	int k;
	ifst >> k;
	switch (k)
	{
	case 1:
		sp = new Rectangle;
		break;
	case 2:
		sp = new Circle;
		break;
	}
	sp->InData(ifst);
	return sp;
}
//----------------------------------------------------------------------------------------------
// �������������
//----------------------------------------------------------------------------------------------
void Rectangle::InData(ifstream& ifst)
{
	ifst >> x >> y;
}
void Rectangle::OutData(ofstream& ofst)
{
	ofst << "�������������: x = " << x << ", y = " << y << endl;
}
int Rectangle::Perimeter() 
{ 
	return 2 * (x + y); 
}
//----------------------------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------------------------
void Circle::InData(ifstream& ifst)
{
	ifst >> r;
}
void Circle::OutData(ofstream& ofst)
{
	ofst << "����: r = " << r << endl;
}
int Circle::Perimeter()
{
	return int(2 * 3.14 * r);
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
	ofst << "��������� ��������:" << endl;
	Node* current = head;
	if (current == NULL)
		return;
	while (current != NULL)
	{
		current->data->OutData(ofst);
		current = current->next;
		ofst << " �������� = " << current->data->Perimeter() << endl;
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