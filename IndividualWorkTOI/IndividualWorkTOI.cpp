// IndividualWorkTOI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"
#include "BinaryTrees.h"
#include "List.h"
#include <vector>

#define ARRAY Arrays::MyArray
#define LIST Lists::List
#define RECORD MyTypes::Image

int ReadValueUInt() {
	int a = 0;
	do {
		std::cin >> a;
		if (a < 0)
			std::cout << "Число должно быть больше либо равно нулю\n";
	} while (a < 0);
	return a;
}

int count = 0;
static bool Intarface(std::vector<std::pair<std::string, void(*)()>> blocks) {
	count++;
	std:: cout <<"Любое число кроме представленных ниже - " << (count == 1 ? "выход из программы" : "выход к предыдущему циклу");
	for (int i = 0; i < blocks.size(); i++)
	{
		std::cout << ((i + 1) + " " + blocks[i].first);
	}
	int number = ReadValueUInt();
	if (number <= 0 || number > blocks.size())
	{
	    count -= 2;
	    return false;
	}
	blocks[number - 1].second();
	std::cout << ("Нажмите Enter для продолжения...");
	std::cin;
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	ARRAY array = ARRAY::GetArrayFromFile("Data.txt");
	array.WriteArray();
	array.AddElems("Data 2.txt");
	array.WriteArray();

	LIST list;
	for(int i = 0 ; i < array.Count(); i++)
		list.SortedPush(array[i], [](RECORD record) { return (int)record.height; },false);
	list.WriteList();
	list.ReverseIter();
	list.WriteList();
	
}

