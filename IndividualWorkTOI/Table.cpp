#include "Array.h";
#include "BTrees.h"
#include "HashTable.h"
#include "List.h"

#include "Table.h"



void Table::TablePTRRecord::SetName(std::string name) {
	record.name = name;
	table->SortAll();
}
void  Table::TablePTRRecord::SetSize(unsigned int size) {
	record.size = size;
	table->SortAll();
}
void  Table::TablePTRRecord::SetWidth(unsigned short width) {
	record.width = width;
	table->SortAll();
}
void  Table::TablePTRRecord::SetHeifht(unsigned short height) {
	record.height = height;
	table->SortAll();
}
void  Table::TablePTRRecord::SetColorDepth(unsigned char colorDepth) {
	record.colorDepth = colorDepth;
	table->SortAll();
}
void Table::TablePTRRecord::SetFormat(std::string format) {
	record.format = format;
	table->SortAll();
}


void Table::SortAll()
{
	tree.DeleteData();
	list.DeleteData();
	for (int i = 0; i < array.Count(); i++) {
		list.PushBack(&array[i]);
		tree.Insert(array[i]);
	}
}

void Table::WriteArray()
{
	array.WriteArray();
}



void Table::WriteSortArray(int criterion, bool rise ) {
	array.SortIndexes(&indexesCrit, criterions[criterion], rise);
	for (size_t i = 0; i < array.Count(); i++)
	{
		std::cout << std::to_string(indexesCrit[i]) << " ";
	}
	std::cout << "\n";
	array.WriteArray(indexesCrit);
}
int  Table::FindInArray(int value, int criterion) {
	array.SortIndexes(&indexesCrit, criterions[criterion]);
	int result = array.FindBinary<int>(indexesCrit,value, criterions[criterion]);
	if (result == -1)
		std::cout << ("Такого записи с таким ключем нет - " + std::to_string(value)) << "\n";
	return result;
}
Table::TablePTRRecord  Table::operator [](int index) {
	return TablePTRRecord(this,array[index]);
}

void  Table::DeleteRecordWhithArray(int value, int criterion) {
	int index = FindInArray(value,criterion);
	if (index == -1) {
		std::cout << "Элемент удалить невозможно\n";
		return;
	}
	RECORD elem = array[index];

	array.DeleteWithNumber(elem.number);
	array.RecoverIndexes();
	SortAll();
}

void  Table::WriteSortArrayWithTree() {
	tree.WriteTreeKeys();
}
RECORD Table::FindWithTree(int value) {
	RECORD elem = tree.Find(value);
	if (elem == RECORD()) {
		std::cout << "Такого ключа в дереве нет\n";
	}
	return elem;
}

void  Table::DeleteRecordFromTree(int value) {
	tree.Delete(value);
	array.RecoverIndexes();
}


void  Table::WriteArrayWithList() {
	list.WriteList();
}
void  Table::WriteSortArrayWithList(int criterion, bool rise) {
	list.WriteList(criterion,rise);
}


RECORD Table::FindRecordWithList(int value, int criterion) {
	RECORD elem = *list.Find(value, criterion);
	if (elem == RECORD()) {
		std::cout << "Такого ключа в списке нет\n";
	}
	return elem;
}


void Table::DeleteRecordFromList(int value, int criterion) {
	list.Remove(value,criterions[criterion]);
	array.RecoverIndexes();
}
