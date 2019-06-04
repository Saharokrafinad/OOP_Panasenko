#include <vector>
#include <string>
#include "pch.h"
#include "../OOP_Panasenko/Program.cpp"
using namespace std;

// Ожидается, что данные, считанные из файла, и добавленные программно совпадут.
TEST(ReadTests, IsReadCorrect)
{
	ifstream CorrectCheckStream("../../OOPTests/ReadTestFile.txt");
	Container actual;
	actual.InitContainer();
	actual.InContainer(CorrectCheckStream);
	Container expected;
	expected.InitContainer();
	expected.Add(new Rectangle(10, 20, 100));
	expected.Add(new Circle(69, 300));
	expected.Add(new Triangle(1, 2, 3, 400));
	Node* actualElement = actual.head;
	Node* expectedElement = expected.head;
	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(actualElement->data->ToString(), expectedElement->data->ToString());
		actualElement = actualElement->next;
		expectedElement = expectedElement->next;
	}
}

// Ожидается, что данные, считанные из файла поменяются местами при сортировке, так как сортировка 
// идет по возрастанию периметра и станут совпадать с добавленными в правльном порядке программно.
TEST(SortTests, IsSortCorrect)
{
	ifstream SortStream("../../OOPTests/SortTestFile.txt");
	Container actual;
	actual.InContainer(SortStream);
	actual.Sort();
	Container expected;
	expected.Add(new Triangle(1, 2, 3, 400));
	expected.Add(new Rectangle(10, 20, 100));
	expected.Add(new Rectangle(100, 200, 100));
	expected.Add(new Rectangle(14, 40, 100));
	expected.Add(new Circle(100, 100));
	Node* actualElement = actual.head;
	Node* expectedElement = expected.head;
	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(actualElement->data->ToString(), expectedElement->data->ToString());
		actualElement = actualElement->next;
		expectedElement = expectedElement->next;
	}
}

// Идет сравнение вычисленных программой периметров
TEST(PerimeterTests, IsPerimeterCorrect)
{
	Triangle triangle = Triangle(1, 2, 3, 100);
	EXPECT_EQ(triangle.Perimeter(), 6);
	Rectangle rectangle = Rectangle(10, 20, 200);
	EXPECT_EQ(rectangle.Perimeter(), 60);
	Circle circle = Circle(10, 300);
	EXPECT_EQ(circle.Perimeter(), 62);
}

bool CompareFiles(string path1, string path2)
{
	string temp;
	ifstream File1(path1);
	vector<string> File1Lines;
	while (File1)
	{
		getline(File1, temp);
		File1Lines.push_back(temp);
	}
	ifstream File2(path2);
	vector<string> File2Lines;
	while (File2)
	{
		getline(File2, temp);
		File2Lines.push_back(temp);
	}
	if (File1Lines.size() != File2Lines.size())
		return false;
	for (int i = 0; i < (int)File1Lines.size(); i++)
		if (File1Lines[i] != File2Lines[i])
			return false;
	return true;
}

TEST(WriteTests, IsWriteCorrect)//Тест на вывод
{
	Container container;
	container.Add(new Rectangle(10, 20, 100));
	container.Add(new Circle(10, 200));
	container.Add(new Triangle(1, 2, 3, 300));
	ofstream WriteStream("../../OOPTests/ActualWriteFile.txt");
	container.OutContainer(WriteStream);
	EXPECT_TRUE(CompareFiles("../../OOPTests/ActualWriteFile.txt", "../../OOPTests/ExpectedWriteFile.txt"));
}

TEST(WriteTests, IsFilteredWriteCorrect)//Тест на фильтровочный вывод
{
	Container container;
	container.Add(new Rectangle(10, 20, 100));
	container.Add(new Circle(10, 200));
	container.Add(new Triangle(1, 2, 3, 300));
	ofstream WriteStream("../../OOPTests/FilteredOutputFile.txt");
	container.OutRectangles(WriteStream);
	EXPECT_TRUE(CompareFiles("../../OOPTests/FilteredOutputFile.txt", "../../OOPTests/ExpectedFilteredOutputFile.txt"));
}