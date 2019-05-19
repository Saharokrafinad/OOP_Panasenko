#include "Program.h"
//----------------------------------------------------------------------------------------------
// Геометрическая фигура
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
// Прямоугольник
//----------------------------------------------------------------------------------------------
void Rectangle::InData(ifstream& ifst)
{
	ifst >> x >> y;
}
void Rectangle::OutData(ofstream& ofst)
{
	ofst << "Прямоугольник: x = " << x << ", y = " << y << endl;
}
//----------------------------------------------------------------------------------------------
// Круг
//----------------------------------------------------------------------------------------------
void Circle::InData(ifstream& ifst)
{
	ifst >> r;
}
void Circle::OutData(ofstream& ofst)
{
	ofst << "Круг: r = " << r << endl;
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
	ofst << "Контейнер содержит:" << endl;
	Node* current = head;
	if (current == NULL)
		return;
	while (current != NULL)
	{
		current->data->OutData(ofst);
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