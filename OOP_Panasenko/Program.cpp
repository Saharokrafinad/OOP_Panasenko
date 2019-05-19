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
bool Shape::Compare(Shape& other)
{
	return Perimeter() < other.Perimeter();
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
	ofst << "Прямоугольник: x = " << x << ", y = " << y;
}
int Rectangle::Perimeter() 
{ 
	return 2 * (x + y); 
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
	ofst << "Круг: r = " << r;
}
int Circle::Perimeter()
{
	return int(2 * 3.14 * r);
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
void Container::Sort()
{
	for (Node* i = head; i; i = i->next)
		for (Node* j = head; j; j = j->next)
			if (i->data->Compare(*(j->data)))
				swap(i->data, j->data);
}