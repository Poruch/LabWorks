
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



void print(std::string str = "", char end = '\n') {
	std::cout << str << end;
}

const int sizeCriterionList = 2;
int (*criterionsForList[])(RECORD&) = { MyTypes::criterionName, MyTypes::criterionHeight };

const int sizeBTree = 2;
int (*criterionBTree)(RECORD&) = MyTypes::criterionSize;



int main()
{
	//Задание с массивом
	////////////////////////// 
	//////////////////////////
	//////////////////////////
	setlocale(LC_ALL, "Russian");
	///// Создание изначального массива
	print("Создание изначального массива");
	ARRAY array = ARRAY::GetArrayFromFile(false ? ReadString() : "Data.txt");
	array.WriteArray();

	/////
	print("Функция сортировки самого массива массива 1");
	///// 

	print("Сортировка самого массива высоте картинки по возрастанию");
	array.Sort(MyTypes::criterionHeight);
	array.WriteArray();

	/////
	print();
	print();
	print("Функция сортировки и вывода по индексам массива 2");
	/////

	print("Сортировка индексов записей по высоте картинки по убыванию");
	int* indexes = new int[0];
	array.SortIndexes(&indexes, MyTypes::criterionHeight, false);
	array.WriteArray(indexes);

	print("Сортировка индексов записей по размеру картинки по убыванию");
	array.SortIndexes(&indexes, MyTypes::criterionSize, false);
	array.WriteArray(indexes);

	/////
	print();
	print();
	print("Функция поиска элементов массива 3");
	/////

	print("Поиск элемента в массиве по значению размера картинки");
	int index = array.Find(165,MyTypes::criterionSize);
	if (index == -1)
		print("Записи с размером картинки - " + std::to_string(165) + " в таблице нет");
	else {
		print("индекс элемента c размером " + std::to_string(165) + " - " + std::to_string(index));
		array[index].Write();
		print();
	}

	print("Поиск элемента в массиве по значению высоты картинки");
	index = array.Find(30000, MyTypes::criterionHeight);
	if (index == -1)
		print("Записи с размером картинки - " + std::to_string(30000) + " в таблице нет");
	else {
		print("индекс элемента - " + std::to_string(index));
		array[index].Write();
		print();
	}
	
	//////
	print();
	print();
	print();
	//////
	
	print("Функция изменения записей в массиве");
	print("Массив до изменения высоты " + std::to_string(array[4].number) + " картинки");
	array.Sort(MyTypes::criterionHeight);
	array.WriteArray();

	array[4].height = 3250;
	array.SortIndexes(&indexes, MyTypes::criterionHeight, false);

	print("Массив после изменения высоты " + std::to_string(array[4].number) + " картинки");
	array.WriteArray(indexes);

	//////
	print();
	print();
	print();
	//////

	print("Функция удаления записи в массиве");
	
	print("Массив до удаления картинки собаки");
	array.Sort(MyTypes::criterionSize);
	array.WriteArray();
	std::string name = "Собака на траве";
	array.DeleteFirstElem<std::string>(name, [](RECORD& record) { return record.name; });

	array.SortIndexes(&indexes, MyTypes::criterionSize, false);
	print("массив после удаления картинки собаки");
	array.WriteArray(indexes);

	//////
	print();
	print();
	print();
	//////
	
	print("Функция добавления записей в массив");
	print("Массив до добавления (отсортирован по 1 букве имени)");
	array.Sort(MyTypes::criterionName);
	array.WriteArray();
	array.AddElems("Data 2.txt");

	print("Массив после добавления");
	array.Sort(MyTypes::criterionName);
	array.WriteArray();
	//////
	print();
	print();
	print();
	//////
	print("Функция удаления записей в массиве");

	print("Массив до удаления картинок с форматом png");
	array.Sort(MyTypes::criterionFormat);
	array.WriteArray();
	name = "png";
	array.DeleteElems<std::string>(name, [](RECORD& record) { return record.format; });


	array.SortIndexes(&indexes, MyTypes::criterionFormat, false);
	print("массив после удаления картинок с форматом png");
	array.WriteArray(indexes);

	//////
	print();
	print();
	print();
	//////

	

	//array.AddElems("Data.txt");

	//Задание с деревом
	////////////////////////// 
	//////////////////////////
	//////////////////////////

	TREE<2> tree = TREE<2>(MyTypes::criterionWidth);
	for (int i = 0; i < array.Count(); i++) {
		tree.Insert(array[i]);
	}


	tree.WriteTreeKeys();
	print();
	print();
	print();
	tree.WriteTree();
	//system("pause");
}

