#include "Program.h"
#include <string>
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
	case 3:
		sp = new Triangle;
		break;
	}
	sp->InData(ifst);
	return sp;
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
	ifst >> x >> y;
	Shape::InData(ifst);
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
Rectangle::Rectangle(int x, int y, int density)
{
	this->x = x;
	this->y = y;
	Shape::density = density;

}
string Rectangle::ToString()
{
	return to_string(x) + " " + to_string(y) + " " + to_string(density);
}
//----------------------------------------------------------------------------------------------
// Круг
//----------------------------------------------------------------------------------------------
void Circle::InData(ifstream& ifst)
{
	ifst >> r;
	Shape::InData(ifst);
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
Circle::Circle(int r, int density)
{
	this->r = r;
	Shape::density = density;
}
string Circle::ToString()
{
	return to_string(r) + " " + to_string(density);
}
//----------------------------------------------------------------------------------------------
// Треугольник
//----------------------------------------------------------------------------------------------
void Triangle::InData(ifstream& ifst)
{
	ifst >> x1 >> x2 >> x3;
	Shape::InData(ifst);
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
Triangle::Triangle(int x1, int x2, int x3, int density)
{
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	Shape::density = density;
}
string Triangle::ToString()
{
	return to_string(x1) + " " + to_string(x2) + " " + to_string(x3) + " " + to_string(density);
}
//----------------------------------------------------------------------------------------------
// Элемент контейнера
//----------------------------------------------------------------------------------------------
Node::Node(Shape* data, Node* next)
{
	this->data = data;
	this->next = next;
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
		Node* temp = new Node(Shape::In(ifst), NULL);
		if (!head)
			head = last = temp;
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
void Container::Add(Shape* shape)
{
	Node* temp = new Node(shape, NULL);
	if (!head)
		head = last = temp;
	else
	{
		last->next = temp;
		last = temp;
	}
}