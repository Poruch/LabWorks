
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"
#include "BTrees.h"
#include "HashTable.h"

#include "List.h"
#include <vector>


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
	srand(time(NULL));
	int criterionInds[2] = { 3,4 };
	setlocale(LC_ALL, "Rus");
	Table table = Table(criterionInds, "Data.txt");


	table.WriteArray();

	table.WriteSortArray(0,false);
	table.WriteSortArray(1,true);

	table.WriteSortArrayWithTree();



	table.WriteArrayWithList();

	table.WriteSortArrayWithList(1);
	table.WriteSortArrayWithList(2);

	table.WriteSortArrayWithList(1,false);
	table.WriteSortArrayWithList(2,false);

	print();
	int index = table.FindInArray(24, 1);
	if(index != -1)
		table[index].Write();

	print();
	table.FindRecordWithList(630,0).Write();
	print();



	table.WriteSortArrayWithList(1, false);
	table.WriteSortArrayWithList(2, false);


	table[4].SetColorDepth(64);
	table[4].SetHeifht(4);

	table.WriteArray();
	table.WriteSortArray(1);
	table.WriteSortArrayWithTree();
	table.WriteArrayWithList();

	table.WriteSortArrayWithList(1);
	table.WriteSortArrayWithList(2);


	table.DeleteRecordWhithArray(64,1);

	table.DeleteRecordFromTree(3223);
	table.DeleteRecordFromTree(1350);
	table.DeleteRecordFromTree(1350);

	table.WriteArray();
	table.WriteSortArray(1);

	table.WriteSortArrayWithTree();
	table.WriteArrayWithList();

	table.WriteSortArrayWithList(1);
	table.WriteSortArrayWithList(2);

	table.DeleteRecordFromList(8, 1);
	table.WriteSortArrayWithList(2);


}

