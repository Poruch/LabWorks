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

	Arrays::GetArrayFromFile(&im, &len,"Data.txt");
	Arrays::WriteArray(im,len);
	Arrays::SortArray(im, len, [](MyTypes::Image image) { return image.width; });
	Arrays::WriteArray(im, len);
	Arrays::SortArray(im, len, [](MyTypes::Image image) { return image.height; });
	Arrays::WriteArray(im, len);
	Arrays::SortArray(im, len, [](MyTypes::Image image) { return (int)image.name[0]; });
	Arrays::WriteArray(im, len);
	std::cout << Arrays::Find(im, len, MyTypes::Image(1, "Луна", 26, 736, 615, 24, "jpg")) << '\n';

	Arrays::SortArray(im, len, [](MyTypes::Image image) { return image.height; });
	Arrays::WriteArray(im, len);
	std::cout << Arrays::FindBinary(im, len, 713, [](MyTypes::Image image) { return image.height; }, 0, len - 1) << '\n';
	int* indexes = 0;
	Arrays::GetSortIndexes(im, &indexes, len, [](MyTypes::Image image) { return image.width; });
	for (int i = 0; i < len; i++)
	{
		std::cout << indexes[i] << " ";
	}
	std::cout << std::endl;
	Arrays::Reconstruct(im,len);
	Arrays::WriteArray(im,len);
	Arrays::DeleteElems(&im, &len, "png", [](MyTypes::Image image) { return image.format; });
	Arrays::WriteArray(im, len);
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
