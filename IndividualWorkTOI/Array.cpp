#include "Array.h"
#include "InputManager.h"
#include <fstream>
#include <string>
#include "MyRecord.h"

#define CONSOLE 1
#define FILE  2

namespace Arrays {
	MyArray::MyArray()
	{
		length = 0;
		records = 0;
	}
	MyArray::MyArray(size_t len)
	{
		length = len;
		records = new RECORD[len];
	}
	MyArray::MyArray(const MyArray& array)
	{
		length = array.length;
		records = array.records;
	}

	MyArray MyArray::GetRandom(size_t length)
	{
		MyArray result(length);
		for (size_t i = 0; i < length; i++)
		{
			
			result[i] = DataManage::InputManager::GetRandomRecord();
			result[i].number = i + 1;
		}
		return result;
	}

	MyArray MyArray::GetArrayFromFile(std::string fileName) {
		std::ifstream file(fileName);
		int len = 0;
		std::string s;
		if (file.is_open()) {
			while (std::getline(file, s)) {
				(len)++;
			}
		}
		else
			return MyArray();
		file.close();
		file = std::ifstream(fileName);
		MyArray result(len);
		if (len == 0) 
			throw "�� ������� ������� ����";
		int i = 0;
		while (i < len) {
			std::getline(file, s);
			result[i] = DataManage::InputManager::GetRecord(FILE,s,'\t');
			i++;
		}
		file.close();
		return result;
	}

	MyArray MyArray::GetArrayFromConsole()
	{
		std::cout << "������� ����� �������" << "\n";
		std::string line = "";
		std::getline(std::cin, line);
		size_t length = std::stoull(line);
		MyArray result(length);
		for (size_t i = 0; i < length; i++)
		{
			result[i] = DataManage::InputManager::GetRecord(CONSOLE);
			result[i].number = i + 1;
		}
		return result;
	}

	void MyArray::WriteArray() {
		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
		for (size_t i = 0; i < length; i++) {
			records[i].Write();
			std::cout << "\n";
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	void MyArray::WriteArray(int* indexes) {
		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
		for (size_t i = 0; i < length; i++) {
			records[indexes[i]].Write();
			std::cout << "\n";
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	void MyArray::Reconstruct() {
		for (int i = 0; i < length; i++) {
			RECORD buff = records[records[i].number - 1];
			records[records[i].number - 1] = records[i];
			records[i] = buff;
		}
	}
	void MyArray::Sort(size_t indStart, size_t indEnd, MyTypes::Criterion criterion, bool rise, bool quick) {
		if (!quick)
			for (size_t i = indStart; i < indEnd - 1; i++) {
				for (size_t j = i + 1; j < indEnd; j++) {
					if (criterion(records[i]) > criterion(records[j]) == rise) {
						auto buff = records[i];
						records[i] = records[j];
						records[j] = buff;
					}
				}
			}
		else {
			QuickSort(records + indStart, indEnd - indStart , criterion, rise);
		}
	}
	void MyArray::Sort(MyTypes::Criterion criterion, bool rise,bool quick ) {
		if(!quick)
		for (int i = 0; i < length - 1; i++) {
			for (int j = i + 1; j < length; j++) {
				if (criterion(records[i]) > criterion(records[j]) == rise) {
					auto buff = records[i];
					records[i] = records[j];
					records[j] = buff;
				}
			}
		}
		else {
			QuickSort(records,length,criterion,rise);
		}
	}

	void MyArray::DeleteWithNumber(size_t value) {
		size_t ind = value - 1;
		InBorder(ind);
		RECORD* result = new RECORD[length - 1];
		size_t j = 0;
		for (size_t i = 0; i < ind; i++)
		{
			result[j++] = records[i];
		}
		for (size_t i = ind + 1; i < length; i++)
		{
			result[j++] = records[i];
		}
		delete[] records;
		records = result;
		length -= 1;
		RecoverIndexes();
	}

	void MyArray::QuickSort(RECORD* array, size_t len, MyTypes::Criterion criterion,bool rise) {
		long long i = 0;
		long long j = len - 1;
		unsigned int mid = criterion(array[len / 2]);
		do {
			if (rise) {
				while (criterion(array[i]) < mid) {
					i++;
				}
				while (criterion(array[j]) > mid) {
					j--;
				}
				if (i <= j) {
					RECORD tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					i++;
					j--;
				}
			}
			else {
				while (criterion(array[i]) > mid) {
					i++;
				}
				while (criterion(array[j]) < mid) {
					j--;
				}
				if (i <= j) {
					RECORD tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					i++;
					j--;
				}
			}
		} while (i <= j);
		if (j > 0) {
			QuickSort(array,j + 1,criterion,rise);
		}
		if (i < len) {
			QuickSort(&array[i], len - i, criterion,rise);
		}
	}

	void MyArray::GetSortIndexes(int* indexes, MyTypes::Criterion criterion, bool rise) {
		for (int i = 0; i < length - 1; i++) {
			for (int j = i + 1; j < length; j++) {
				if ((criterion(records[indexes[i]]) > criterion(records[indexes[j]])) == rise) {
					auto buff = indexes[i];
					indexes[i] = indexes[j];
					indexes[j] = buff;
				}
			}
		}
	}

	void MyArray::SortIndexes(int** indexes, MyTypes::Criterion criterion, bool rise, bool quick) {
		delete[](*indexes);
		(*indexes) = new int[Count()];
		for (int i = 0; i < Count(); i++) {
			(*indexes)[i] = i;
		}
		if (quick) {
			QuickGetSortIndexes((*indexes), Count(), criterion, rise);
		}
		else {
			GetSortIndexes((*indexes), criterion, rise);
		}
	}

	void MyArray::QuickGetSortIndexes(int* indexes, size_t len, MyTypes::Criterion criterion, bool rise) {
		long long i = 0;
		long long j = len - 1;
		unsigned int mid = criterion(records[indexes[len / 2]]);
		do {
			if (rise) {
				while (criterion(records[indexes[i]]) < mid) {
					i++;
				}
				while (criterion(records[indexes[j]]) > mid) {
					j--;
				}
				if (i <= j) {
					int tmp = indexes[i];
					indexes[i] = indexes[j];
					indexes[j] = tmp;
					i++;
					j--;
				}
			}
			else {
				while (criterion(records[indexes[i]]) > mid) {
					i++;
				}
				while (criterion(records[indexes[j]]) < mid) {
					j--;
				}
				if (i <= j) {
					int tmp = indexes[i];
					indexes[i] = indexes[j];
					indexes[j] = tmp;
					i++;
					j--;
				}
			}
		} while (i <= j);
		if (j > 0) {
			QuickGetSortIndexes(indexes, j + 1, criterion, rise);
		}
		if (i < len) {
			QuickGetSortIndexes(&indexes[i], len - i, criterion, rise);
		}
	}
	int MyArray::Find(RECORD value) {
		for (int i = 0; i < length; i++)
			if (records[i] == value)
				return i;
		return -1;
	}

	void MyArray::RecoverIndexes(bool rise) {
		int* indexes = 0;
		SortIndexes(&indexes, [](RECORD& image) {return (unsigned int)image.number; }, rise);
		for (int i = 0; i < length; i++) {
			records[indexes[i]].number = i + 1;
		}
		delete[] indexes;
	}

	void MyArray::DeleteFirstElem(RECORD value) {
		int ind = Find(value);
		if (ind == -1)
			return;
		RECORD* currentArray = new RECORD[length - 1];
		int j = 0;
		for (int i = 0; i < ind; i++)
		{
			currentArray[j++] = records[i];
		}
		for (int i = ind + 1; i < length; i++)
		{
			currentArray[j++] = records[i];
		}
		delete[] records;
		records = currentArray;
		length -= 1;
		RecoverIndexes();
	}
	void MyArray::AddElem(RECORD value) {
		size_t newLen = 1 + length;
		ReSize(newLen);
		records[length] = value;
		length = newLen;
	}

	void MyArray::AddElems(int count) {
		size_t newLen = count + length;
		RECORD* result = new RECORD[newLen];

		for (int i = 0; i < length; i++) {
			result[i] = records[i];
		}
		for (int i = length; i < newLen; i++) {
			result[i] = DataManage::InputManager::GetRecord(CONSOLE);
		}
		delete[] records;

		records = result;
		length = newLen;
	}

	void MyArray::AddElems(std::string fileName) {
		MyArray addRecords = GetArrayFromFile(fileName);
		size_t newLen = addRecords.Count() + length;
		RECORD* result = new RECORD[newLen];
		int count = 1;
		for (int i = 0; i < length; i++) {
			result[i] = records[i];
			count++;
		}
		for (int i = 0; i < addRecords.Count(); i++) {
			result[i + length] = addRecords[i];
			result[i + length].number = count++;
		}
		delete[] records;

		records = result;
		length = newLen;
	}

	

	void MyArray::ReSize(size_t newLen) {
		RECORD* newRecords = new RECORD[newLen];
		for (int i = 0; i < length; i++) {
			newRecords[i] = records[i];
		}
		delete[] records;
		records = newRecords;
	}
}