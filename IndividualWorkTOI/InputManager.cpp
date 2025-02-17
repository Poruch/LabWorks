#include "InputManager.h"
#include "MyRecord.h"
#include <string>
#include <iostream>

MyTypes::Image DataManage::InputManager::GetRecord(int from, std::string line, char separator) {
	MyTypes::Image result = MyTypes::Image();
	if (from & 1) 
		std::getline(std::cin, line);
	int last = 0;
	int a = -1;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == separator) {
			switch (a)
			{
			case -1:
				result.number = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 0:
				result.name = line.substr(last, i - last);
				last = i + 1;
				a++;
				break;
			case 1:
				result.size = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 2:
				result.width = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 3:
				result.height = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 4:
				result.colorDepth = (unsigned char)stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			}
		}
		result.format = line.substr(last, line.size() - last);
	}
	return result;
}

MyTypes::Image DataManage::InputManager::GetRandomRecord() {
	MyTypes::Image result = MyTypes::Image();
	
	return result;
}