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
	ifst >> x >> y;
	Shape::InData(ifst);
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
void Rectangle::MultiMethod(Shape* other, ofstream& ofst)
{
	other->MMRectangle(ofst);
}

void Rectangle::MMRectangle(ofstream& ofst)
{
	ofst << "������������� � �������������" << endl;
}

void Rectangle::MMCircle(ofstream& ofst)
{
	ofst << "���� � �������������" << endl;
}

void Rectangle::MMTriangle(ofstream& ofst)
{
	ofst << "����������� � �������������" << endl;
}
//----------------------------------------------------------------------------------------------
// ����
//----------------------------------------------------------------------------------------------
void Circle::InData(ifstream& ifst)
{
	ifst >> r;
	Shape::InData(ifst);
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
void Circle::MultiMethod(Shape* other, ofstream& ofst)
{
	other->MMCircle(ofst);
}

void Circle::MMRectangle(ofstream& ofst)
{
	ofst << "����������� � ����" << endl;
}

void Circle::MMCircle(ofstream& ofst)
{
	ofst << "���� � ����" << endl;
}

void Circle::MMTriangle(ofstream& ofst)
{
	ofst << "����������� � ����" << endl;
}
//----------------------------------------------------------------------------------------------
// �����������
//----------------------------------------------------------------------------------------------
void Triangle::InData(ifstream& ifst)
{
	ifst >> x1 >> x2 >> x3;
	Shape::InData(ifst);
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
void Triangle::MultiMethod(Shape* other, ofstream& ofst)
{
	other->MMTriangle(ofst);
}

void Triangle::MMRectangle(ofstream& ofst)
{
	ofst << "������������� � �����������" << endl;
}

void Triangle::MMCircle(ofstream& ofst)
{
	ofst << "���� � �����������" << endl;
}

void Triangle::MMTriangle(ofstream& ofst)
{
	ofst << "����������� � �����������" << endl;
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
void Container::MultiMethod(ofstream& ofst)
{
	ofst << "�����������:" << endl;
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