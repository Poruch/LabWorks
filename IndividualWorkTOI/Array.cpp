#include "Array.h"
#include "InputManager.h"
#include <fstream>
#include <string>
#include "MyRecord.h"

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
		if (*len != 0)
			(*arr) = new Image[*len];
		else
			return;
		int i = 0;
		while (i < *len) {
			std::getline(file, s);
			(*arr)[i] = DataManage::InputManager::GetRecord(s);
			i++;
		}
		file.close();
	}

	void GetArray(Image** arr, int len) {
		(*arr) = new Image[len];
		for (int i = 0; i < len; i++) {
			(*arr)[i] = DataManage::InputManager::GetRecord();
		}
	}
	void WriteArray(Image* arr, int len) {
		for (int i = 0; i < len; i++) {
			arr[i].Write();
			std::cout << "\n";
		}
	}
	void SortArray(Image* arr, int len, int (*criterion)(Image)) {

	}
	void FindElem(Image* arr, int len, Image image, int idCriterion) {

	}
	void DeleteElem(Image** arr, int len, Image image, int idCriterion) {

	}
}