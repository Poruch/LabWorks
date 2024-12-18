// IndividualWorkTOI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"


int main()
{
	setlocale(LC_ALL, "Russian");
	MyTypes::Image* im = 0;
	int len = 0;

	MyTypes::GetArrayFromFile(&im, &len,"Data.txt");
	MyTypes::WriteArray(im,len);
	MyTypes::SortArray(im, len, [](MyTypes::Image image) { return image.width; });
	MyTypes::WriteArray(im, len);
	MyTypes::SortArray(im, len, [](MyTypes::Image image) { return image.height; });
	MyTypes::WriteArray(im, len);
	MyTypes::SortArray(im, len, [](MyTypes::Image image) { return (int)image.name[0]; });
	MyTypes::WriteArray(im, len);
	std::cout << MyTypes::Find(im, len, MyTypes::Image(1, "Луна", 26, 736, 615, 24, "jpg")) << '\n';

	MyTypes::SortArray(im, len, [](MyTypes::Image image) { return image.colorDepth; });
	MyTypes::WriteArray(im, len);
	std::cout << MyTypes::FindBinary(im, len, 8, [](MyTypes::Image image) { return image.colorDepth; }) << '\n';
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
