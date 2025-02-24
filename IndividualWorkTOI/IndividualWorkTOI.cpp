
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"
#include "BTrees.h"
#include "HashTable.h"

#include <Windows.h>
#include "List.h"

#include "Table.h"
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int criterionInds[2] = { 3,0 };
	setlocale(LC_ALL, "Rus");

	int action = 1;
	bool flag = false;
	print("Введите 1 для заполения из файла");
	print("Введите 2 для заполнения из консоли");
	print("Введите 3 для заполнения случайными полями");

	
	Table table = Table(criterionInds, "Data.txt");
	do {
		action = ReadValueUInt();
		switch (action)
		{
		case 1:
			flag = true;
			break;
		case 2:
			flag = true;
			table = Table(criterionInds);
			table.SortAll();
			break;
		case 3:
			flag = true;
			print("Введите длину массива");
			table = Table(criterionInds, ReadValueUInt());
			table.SortAll();
			break;
		default:
			print("Введите цифру нормально");
			break;
		}
	} while (!flag);
	flag = true;


	ARRAY array = ARRAY::GetArrayFromFile("Data.txt");
	TABLE hashTable = TABLE(array.Count());
	for (size_t i = 0; i < array.Count(); i++)
	{
		hashTable.AddPair(array[i].name,array[i]);
	}
	hashTable.GetValue("Собака на траве").Write();
	print();
	hashTable.GetValue("sasdasd").Write();
	print();
	hashTable.GetValue("Бабочка").Write();
	print();
	hashTable.AddPair("asd", RECORD(2,"asd", 2, 2, 2,2, "dsds"));
	hashTable.GetValue("asd").Write();

	print("Исходная таблица");
	table.WriteArray();
	print("Лист");
	table.WriteArrayWithList();
	print("Дерево");
	table.WriteSortArrayWithTree();

	system("pause");
	RECORD record = RECORD();
	int index = 0;
	int value = 0;
	int findIndex = 0;
	std::string line;
	system("pause");
	while (action != -1) {
		system("cls");
		print("Первый критерий - высота, он используется в дереве");
		print("Второй критерий - Имя");

		print("1. работа с массивом");
		print("2. работа с деревом");
		print("3. работа со списком");
		do {
			if(flag)
				action = ReadValueUInt();
			switch (action)
			{				
			case 1:
				system("cls");
				table.WriteArray();
				print("1. - Отсортировать по имени");
				print("2. - Отсортировать по высоте");
				print("3. - удалить элемент");
				print("4. - найти элемент");
				do {
					action = ReadValueUInt();
					switch (action)
					{
					case 1:
						table.WriteSortArray(1);
						break;
					case 2:
						table.WriteSortArray(0);
						break;
					case 3:
						print("Введите индекс ключа (0, 1) и значение которое хотите удалить");
						index = ReadValueUInt();
						value = ReadValueUInt();
						if (index > 1)
							break;
						table.DeleteRecordWhithArray(value,index);
						break;
					case 4:
						print("Введите индекс ключа (0, 1) и значение которое хотите найти");
						index = ReadValueUInt(); 
						if (index > 1)
							break;
						if (index == 0) {
							value = ReadValueUInt();
							findIndex = table.FindInArray(value, index);
						}
						if (index == 1) {
							line = ReadString();
							findIndex = table.FindInArray(MyTypes::GetIntFromString(line), index);
						}				
						if (findIndex != -1) {
							table[findIndex].Write();
							print();
						}
						else{
							print("Такого элемента нет");
						}
						break;
					default:
						flag = true;
						break;
					}
				} while (!flag);

				system("pause");

				break;
			case 2:
				system("cls");
				table.WriteSortArrayWithTree();
				print("1. - удалить элемент");
				print("2. - найти элемент");
				do {
					action = ReadValueUInt();
					switch (action)
					{
					case 1:
						print("Введите значение которое хотите удалить (Высота)");
						value = ReadValueUInt();
						table.DeleteRecordFromTree(value);
						break;
					case 2:
						print("Введите значение которое хотите найти(Высота)");
						value = ReadValueUInt();
						record = table.FindWithTree(value);
						record.Write();
						if (record == RECORD())
							print("Такой записи нет в дереве");
						print();
						break;					
					default:
						flag = true;
						break;
					}
				} while (!flag);
				system("pause");


				break;
			case 3:
				system("cls");
				table.WriteArrayWithList();
				print("1. - Отсортировать по имени");
				print("2. - Отсортировать по высоте");
				print("3. - удалить элемент");
				print("4. - найти элемент");
				do {
					action = ReadValueUInt();
					switch (action)
					{
					case 1:
						table.WriteSortArrayWithList(2);
						break;
					case 2:
						table.WriteSortArrayWithList(1);
						break;
					case 3:
						print("Введите индекс ключа (0, 1) и значение которое хотите удалить");
						index = ReadValueUInt();
						value = ReadValueUInt();
						if (index > 1)
							break;
						table.DeleteRecordFromList(value, index);
						break;
					case 4:
						print("Введите индекс ключа (0, 1) и значение которое хотите найти");
						index = ReadValueUInt(); 
						if (index > 1)
							break;
						if (index == 0) {
							value = ReadValueUInt();
							record = table.FindRecordWithList(value, index);
						}
						if (index == 1) {
							line = ReadString();
							record = table.FindRecordWithList(MyTypes::GetIntFromString(line), index);
						}						
						record.Write();
						if (record == RECORD())
							print("Такой записи нет в листе");
						break;
					default:
						flag = true;
						break;
					}
				} while (!flag);

				system("pause");

				break;
			default:
				flag = true;
				break;
			}
		} while (!flag);
	}

}

