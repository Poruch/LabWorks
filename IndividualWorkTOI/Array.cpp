#include "Array.h"
#include "InputManager.h"
#include <fstream>
#include <string>
#include "MyRecord.h"

#define CONSOLE 1
#define FILE  2

namespace MyTypes {
	void GetArrayFromFile(Image** arr, int* len, std::string fileName) {
		std::ifstream file(fileName);
		std::string s;
		if (file.is_open()) {
			while (std::getline(file, s)) {
				(*len)++;
			}
		}
		else
			return;
		file.close();
		file = std::ifstream(fileName);
		if (*len != 0) {
			delete[](*arr);
			(*arr) = new Image[*len];
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

	void GetArray(Image** arr, int len) {
		delete[] (*arr);
		(*arr) = new Image[len];
		for (int i = 0; i < len; i++) {
			(*arr)[i] = DataManage::InputManager::GetRecord(CONSOLE);
		}
	}
	void WriteArray(Image* arr, int len) {
		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number///Name///Size///Width///Height///ColorDepth///Format///\n";
		for (int i = 0; i < len; i++) {
			arr[i].Write();
			std::cout << "\n";
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}
	void SortArray(Image* arr, int len, int (*criterion)(Image), bool rise) {
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

	int FindBinary(Image* arr, int len, int value, int (*criterion)(Image)) {
		int offsetLeft = 0;
		int offsetRight = len / 2;
		while (offsetLeft + offsetRight != 0 && offsetLeft + offsetRight != len - 1)
		{
			if (criterion(arr[offsetLeft + offsetRight]) == value)
				return offsetLeft + offsetRight;
			else if (criterion(arr[offsetLeft + offsetRight]) > value)
			{
				offsetRight /= 2;
			}
			else if (criterion(arr[offsetLeft + offsetRight]) < value)
			{
				offsetLeft += offsetRight;
				offsetRight /= 2;
			}
		}
		if (criterion(arr[0]) == value)
			return offsetLeft + offsetRight;
		if (criterion(arr[len-1]) == value)
			return offsetLeft + offsetRight;
		return -1;
	}

	int FindBinary(Image* arr, int len, std::string value, std::string (*criterion)(Image)) {
		int offsetLeft = 0;
		int offsetRight = len / 2;
		while (offsetRight != 0)
		{
			if (criterion(arr[offsetLeft + offsetRight]) == value)
				return offsetLeft + offsetRight;
			else if (criterion(arr[offsetLeft + offsetRight]) > value)
			{
				offsetRight /= 2;
			}
			else if (criterion(arr[offsetLeft + offsetRight]) < value)
			{
				offsetLeft += offsetRight;
				offsetRight /= 2;
			}
		}
		return -1;
	}

	int Find(Image* arr, int len, Image value) {
		for (int i = 0; i < len; i++)
			if (arr[i] == value)
				return i;
		return -1;
	}

	int DeleteElems(Image** arr, int len, int value, int(*criterion)(Image)) {

	}
	int DeleteElems(Image** arr, int len, std::string value, std::string(*criterion)(Image)) {

	}
	int DeleteFirstElem(Image** arr, int len, int value, int(*criterion)(Image)) {

	}
	int DeleteFirstElem(Image** arr, int len, std::string value, std::string(*criterion)(Image)) {

	}

	int DeleteFirstElem(Image** arr, int len, Image value) {
		int ind = Find((*arr), len, value);
		if (ind == -1)
			return;		
		Image* currentArray = new Image[len - 1];
		int j = 0;
		for (int i = 0; i < ind; i++)
		{
			currentArray[j++] = (*arr)[i];
		}
		for (int i = ind + 1; i < len; i++)
		{
			currentArray[j++] = (*arr)[i];
		}
		delete[](*arr);
		(*arr) = currentArray;
	}
}