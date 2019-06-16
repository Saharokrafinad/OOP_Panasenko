#include "Program.h"
//----------------------------------------------------------------------------------------------
// Геометрическая фигура
//----------------------------------------------------------------------------------------------
Shape* Shape::In(ifstream& ifst)
{
	Shape* type = NULL;
	int index;
	ifst >> index;
	switch (index)
	{
	case 1:
		type = new Rectangle;
		break;
	case 2:
		type = new Circle;
		break;
	case 3:
		type = new Triangle;
		break;
	}
	type->InData(ifst);
	return type;
}
void Shape::InData(ifstream& ifst)
{
	ifst >> density;
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
	ifst >> side1 >> side2;
	Shape::InData(ifst);
}
void Rectangle::OutData(ofstream& ofst)
{
	ofst << "Прямоугольник: x = " << side1 << ", y = " << side2;
	Shape::OutData(ofst);
}
int Rectangle::Perimeter() 
{ 
	return 2 * (side1 + side2); 
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
	ifst >> radius;
	Shape::InData(ifst);
}
void Circle::OutData(ofstream& ofst)
{
	ofst << "Круг: r = " << radius;
	Shape::OutData(ofst);
}
int Circle::Perimeter()
{
	return int(2 * 3.14 * radius);
}
//----------------------------------------------------------------------------------------------
// Треугольник
//----------------------------------------------------------------------------------------------
void Triangle::InData(ifstream& ifst)
{
	ifst >> side1 >> side2 >> side3;
	Shape::InData(ifst);
}
void Triangle::OutData(ofstream& ofst)
{
	ofst << "Треугольник: x1 = " << side1 << ", x2 = " << side2 << ", x3 = " << side3;
	Shape::OutData(ofst);
}
int Triangle::Perimeter()
{
	return int(side1 + side2 + side3);
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