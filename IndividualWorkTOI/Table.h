#pragma once
#include "Array.h";
#include "BTrees.h"
#include "HashTable.h"
#include "List.h"


struct Table {
private:
	ARRAY array = ARRAY();
	LIST<2> list;
	TREE<2> tree;	

	int* indexesCrit = 0;
	MyTypes::Criterion criterions[2];
public:

	Table(int criterionInds[2], std::string filename) {
		array = ARRAY::GetArrayFromFile(filename);
		list = LIST<2>(criterionInds);
		tree = TREE<2>(criterionInds[0]);
		for (size_t i = 0; i < 2; i++)
		{
			this->criterions[i] = MyTypes::criterions[criterionInds[i]];
		}
		for (int i = 0; i < array.Count(); i++) {
			list.PushBack(&array[i]);
			tree.Insert(array[i]);
		}
	}
	Table(int criterionInds[2],int length) {
		array = ARRAY::GetRandom(length);
		list = LIST<2>(criterionInds);
		tree = TREE<2>(criterionInds[0]);
		for (size_t i = 0; i < 2; i++)
		{
			this->criterions[i] = MyTypes::criterions[criterionInds[i]];
		}
		for (int i = 0; i < array.Count(); i++) {
			list.PushBack(&array[i]);
			tree.Insert(array[i]);
		}
	}
	Table() {
	}
	Table(int criterionInds[2]) {
		array = ARRAY::GetArrayFromConsole();
		list = LIST<2>(criterionInds);
		tree = TREE<2>(criterionInds[0]);
		for (size_t i = 0; i < 2; i++)
		{
			this->criterions[i] = MyTypes::criterions[criterionInds[i]];
		}
		for (int i = 0; i < array.Count(); i++) {
			list.PushBack(&array[i]);
			tree.Insert(array[i]);
		}
	}
	struct TablePTRRecord {
		void Write() {
			record.Write();
		}
		void SetName(std::string name);
		void SetSize(unsigned int size);
		void SetWidth(unsigned short width);
		void SetHeight(unsigned short height);
		void SetColorDepth(unsigned char colorDepth);
		void SetFormat(std::string format);

		TablePTRRecord(Table* table, RECORD& record) :record(record), table(table) {};

	private:
		RECORD& record;
		Table* table;
	};

	void SortAll();

	void WriteArray();

	void WriteSortArray(int criterion,bool rise = true);
	int FindInArray(unsigned int value, int criterion);
	TablePTRRecord operator [](int index);
	void DeleteRecordWhithArray(unsigned value, int criterion);

	void WriteSortArrayWithTree(bool rise = true);
	RECORD FindWithTree(unsigned int value);
	void DeleteRecordFromTree(unsigned int value);


	void WriteArrayWithList();
	void WriteSortArrayWithList(int criterion, bool rise = true);
	RECORD FindRecordWithList(unsigned int value, int criterion);
	void DeleteRecordFromList(unsigned int value, int criterion);
};