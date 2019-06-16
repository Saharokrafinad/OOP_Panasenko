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
void Rectangle::MultiMethod(Shape* other, ofstream& ofst)
{
	other->MMRectangle(ofst);
}
void Rectangle::MMRectangle(ofstream& ofst)
{
	ofst << "Прямоугольник и прямоугольник" << endl;
}
void Rectangle::MMCircle(ofstream& ofst)
{
	ofst << "Круг и прямоугольник" << endl;
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
void Circle::MultiMethod(Shape* other, ofstream& ofst)
{
	other->MMCircle(ofst);
}
void Circle::MMRectangle(ofstream& ofst)
{
	ofst << "Прямоугольник и круг" << endl;
}
void Circle::MMCircle(ofstream& ofst)
{
	ofst << "Круг и круг" << endl;
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
void Container::MultiMethod(ofstream& ofst)
{
	ofst << "Multimethod." << endl;
	Node* i = head;
	while (i->next)
	{
		Node* j = i->next;
		while (j)
		{
			i->data->MultiMethod(j->data, ofst);
			j = j->next;
		}
		i = i->next;
	}
}