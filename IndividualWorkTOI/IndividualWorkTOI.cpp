
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"
#include "BinaryTrees.h"
#include "HashTable.h"

#include "List.h"
#include <vector>

#define ARRAY Arrays::MyArray
#define LIST Lists::List
#define RECORD MyTypes::Image
#define TABLE HashTables::HashTable
#define TREE Trees::BTree


int ReadValueUInt() {
	int a = 0;
	do {
		std::cin >> a;
		std::cin.ignore();
		if (a < 0)
			std::cout << "Число должно быть больше либо равно нулю\n";
	} while (a < 0);
	return a;
}
std::string ReadString() {
	std::string result = "";
	std::getline(std::cin,result);
	return result;
}

int static criterionName(RECORD value) {
	return (int)value.name[0];
}
int static criterionHeight(RECORD value) {
	return (int)value.height;
}
int static criterionWidth(RECORD value) {
	return (int)value.width;
}
int static criterionColorDepth(RECORD value) {
	return (int)value.colorDepth;
}
int static criterionSize(RECORD value) {
	return (int)value.size;
}
int static criterionFormat(RECORD value) {
	return (int)value.format[0];
}
void print(std::string str,char end = '\n') {
	std::cout << str << end;
}

int (* const criterions[6])(RECORD) = { criterionName, criterionSize, criterionWidth, criterionHeight, criterionColorDepth, criterionFormat };


int main()
{
	
	setlocale(LC_ALL, "Russian");
	ARRAY array = ARRAY::GetArrayFromFile(false ? ReadString() : "Data.txt");
	/*	print("Введите название txt файла из которго создасться таблица");	
	print("Таблица:");
	array.WriteArray();
	print("Выберите 2 ключа для сортировок (1,2,3,4,5,6)");
	int typeCrit = ReadValueUInt();
	auto crit1 = criterions[typeCrit- 1];
	typeCrit = ReadValueUInt();
	auto crit2 = criterions[typeCrit - 1];
	print("Введите хотите работать с массивом (1) со списком (2) или с деревом (3)");

	int task = ReadValueUInt();
	system("cls");
	switch (task)
	{
	case 1:
		break;
		print("Вы работаете с массивом");
		while (true) {

		}
	case 2: {		
		LIST list[3]{ LIST(), LIST(), LIST() };
		for (size_t i = 0; i < array.Count(); i++)
		{
			list[0].SortedPush(array[i], crit1);
			list[1].SortedPush(array[i], crit2);
			list[2].PushBack(array[i]);
		}
		while (true) {
			system("cls");
			print("Вы работаете со списком");
			print("1 - вывести отсортированную таблицу по 1 критерию");
			print("2 - вывести отсортированную таблицу по 2 критерию");
			print("3 - вывести таблицу в порядке заполнения");
			int action = ReadValueUInt();
			switch (action)
			{
			case 1:
				list[0].WriteList();
				break;
			case 2:
				list[1].WriteList();
				break;
			case 3:
				list[2].WriteList();
				break;
			default:
				break;
			}
			system("pause");
		}
	}
		break;
	case 3:
		print("Вы работаете с деревом");
		TREE<2,>
		while (true) {

		}
		break;
	default:
		break;
	}*/
	int (*crits[1])(RECORD) = { criterionName };
	LIST<2> list = LIST<2>(crits);
}

