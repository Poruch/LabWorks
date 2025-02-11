﻿// IndividualWorkTOI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"
#include "BinaryTrees.h"
#include "List.h"
#include <vector>

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

	MyTypes::Image* im = 0;
	int len = 0;
	Arrays::GetArrayFromFile(&im, &len,"Data.txt");
	Arrays::WriteArray(im,len);	
	Arrays::AddElems(&im,&len, "Data 2.txt");
	Arrays::WriteArray(im, len);

	Lists::ListNode<int>* list = new Lists::ListNode<int>(0, MyTypes::Image());
	Lists::GetList<int>(&list, im, len, [](MyTypes::Image im) { return (int)im.height; });
	std::cout << "\n";
	Lists::WriteList<int>(list, [](MyTypes::Image im) { return (int)im.height; });
	std::cout << "\n";
	list = Lists::GetReverseListRec(list);
	Lists::WriteList<int>(list, [](MyTypes::Image im) { return (int)im.height; });
}

