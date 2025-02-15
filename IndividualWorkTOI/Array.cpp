#include "Array.h"
#include "InputManager.h"
#include <fstream>
#include <string>
#include "MyRecord.h"

#define CONSOLE 1
#define FILE  2
#define RECORD MyTypes::Image

namespace Arrays {
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
			return;
		file.close();
		file = std::ifstream(fileName);
		if (len != 0) {
			delete[](*arr);
			(*arr) = new MyTypes::Image[len];
		}
		else
			throw "Не удалось открыть файл";
		int i = 0;
		while (i < *len) {
			std::getline(file, s);
			(*arr)[i] = DataManage::InputManager::GetRecord(FILE,s,'\t');
			i++;
		}
		file.close();
	}

	void GetArray(MyTypes::Image** arr, int len) {
		delete[] (*arr);
		(*arr) = new MyTypes::Image[len];
		for (int i = 0; i < len; i++) {
			(*arr)[i] = DataManage::InputManager::GetRecord(CONSOLE);
		}
	}
	void WriteArray(MyTypes::Image* arr, int len) {
		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number///Name///Size///Width///Height///ColorDepth///Format///\n";
		for (int i = 0; i < len; i++) {
			arr[i].Write();
			std::cout << "\n";
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	void Reconstruct(MyTypes::Image* arr, int len) {
		for (int i = 0; i < len; i++) {
			MyTypes::Image buff = arr[arr[i].number - 1];
			arr[arr[i].number - 1] = arr[i];
			arr[i] = buff;
		}
	}

	void SortArray(MyTypes::Image* arr, int len, int (*criterion)(MyTypes::Image), bool rise) {
		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len; j++) {
				if (criterion(arr[i]) > criterion(arr[j]) == rise) {
					auto buff = arr[i];
					arr[i] = arr[j];
					arr[j] = buff;
				}
			}
		}
	}


	template
	void MyArray::GetSortIndexes(int** indexes, std::string(*criterion)(MyTypes::Image), bool rise) {
		delete[] (*indexes);
		(*indexes) = new int[length];
		for (int i = 0; i < length; i++)
			(*indexes)[i] = i;

		for (int i = 0; i < length - 1; i++) {
			for (int j = i + 1; j < length; j++) {
				if ((criterion(records[(*indexes)[i]]) > criterion(records[(*indexes)[j]])) == rise) {
					auto buff = (*indexes)[i];
					(*indexes)[i] = (*indexes)[j];
					(*indexes)[j] = buff;
				}
			}
		}
	}


	int FindBinary(MyTypes::Image* arr, int len, int value, int (*criterion)(MyTypes::Image)) {
		int offsetLeft = 0;
		int offsetRight = len - 1;
		while (offsetLeft <= offsetRight) {
			int m = (offsetLeft + offsetRight) / 2;
			if (criterion(arr[m]) < value)
				offsetLeft = m + 1;
			else if (criterion(arr[m]) > value)
				offsetRight = m - 1;
			else
				return m;
		}
		return -1;
	}

	int FindBinary(MyTypes::Image* arr, int len, std::string value, std::string (*criterion)(MyTypes::Image)) {
		int offsetLeft = 0;
		int offsetRight = len - 1;
		while (offsetLeft <= offsetRight) {
			int m = (offsetLeft + offsetRight) / 2;
			if (criterion(arr[m]) < value)
				offsetLeft = m + 1;
			else if (criterion(arr[m]) > value)
				offsetRight = m - 1;
			else
				return m;
		}
		return -1;
	}
	int FindBinary(MyTypes::Image* arr, int len, std::string value, std::string(*criterion)(MyTypes::Image), 
		int offsetLeft, int offsetRight) {
		int m = (offsetLeft + offsetRight) / 2;
		if (offsetLeft > offsetRight)
			return -1;
		if (criterion(arr[m]) < value)
			return FindBinary(arr, len, value, criterion, m + 1, offsetRight);
		else if (criterion(arr[m]) > value)
			return FindBinary(arr, len, value, criterion, offsetLeft, m - 1);
		else
			return m;
	}
	int FindBinary(MyTypes::Image* arr, int len, int value, int(*criterion)(MyTypes::Image),
		int offsetLeft, int offsetRight) {
		int m = (offsetLeft + offsetRight) / 2;
		if (offsetLeft > offsetRight)
			return -1;
		if (criterion(arr[m]) < value)
			return FindBinary(arr, len, value, criterion, m + 1, offsetRight);
		else if (criterion(arr[m]) > value)
			return FindBinary(arr, len, value, criterion, offsetLeft, m - 1);
		else
			return m;
	}
	int MyArray::Find(RECORD value) {
		for (int i = 0; i < length; i++)
			if (records[i] == value)
				return i;
		return -1;
	}

	void MyArray::RecoverIndexes(bool rise) {
		int* indexes = 0;
		GetSortIndexes(&indexes, [](MyTypes::Image image) {return (int)image.number; }, rise);
		for (int i = 0; i < len; i++) {
			arr[indexes[i]].number = i + 1;
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
		int newLen = 1 + length;
		ReSize(newLen);
		records[length] = value;
		length = newLen;
	}

	void AddElems(MyTypes::Image** arr, int* len, int count) {		
		int newLen = count + *len;
		MyTypes::Image* result = new MyTypes::Image[newLen];
		for (int i = 0; i < *len; i++) {
			result[i] = (*arr)[i];
		}
		for (int i = *len; i < newLen; i++) {
			result[i] = DataManage::InputManager::GetRecord(CONSOLE);
		}
		delete[](*arr);

		(*arr) = result;
		*len = newLen;
	}

	void AddElems(MyTypes::Image** arr, int* len, std::string fileName) {
		MyTypes::Image* arr2 = 0;
		int len2 = 0;
		GetArrayFromFile(&arr2,&len2,fileName);
		int newLen = len2 + *len;
		MyTypes::Image* result = new MyTypes::Image[newLen];
		int count = 1;
		for (int i = 0; i < *len; i++) {
			result[i] = (*arr)[i];
			count++;
		}
		for (int i = 0; i < len2; i++) {
			result[i + *len] = arr2[i];
			result[i + *len].number = count++;
		}
		delete[] arr2;
		delete[] (*arr);

		(*arr) = result;
		*len = newLen;
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