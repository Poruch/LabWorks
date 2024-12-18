#include "InputManager.h"
#include "MyRecord.h"
#include <string>
#include <iostream>

MyTypes::Image DataManage::InputManager::GetRecord() {
	MyTypes::Image result = MyTypes::Image();
	std::string s = "";
	std::getline(std::cin,s);
	int last = 0;
	int a = -1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			switch (a)
			{
			case -1:
				result.number = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 0:
				result.name = s.substr(last, i);
				last = i + 1;
				a++;
				break;
			case 1:
				result.size = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 2:
				result.width = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 3:
				result.height = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 4:
				result.colorDepth = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			}
		}
		result.format = s.substr(last, s.size());
	}
	return result;
}
MyTypes::Image DataManage::InputManager::GetRecord(std::string line) {
	MyTypes::Image result = MyTypes::Image();
	if (line == "")
		return result;
	std::string s = line;
	
	int last = 0;
	int a = -1;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '\t') {
			switch (a)
			{
			case -1:
				result.number = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 0:
				result.name = s.substr(last, i);
				last = i + 1;
				a++;
				break;
			case 1:
				result.size = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 2:
				result.width = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 3:
				result.height = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			case 4:
				result.colorDepth = stoi(s.substr(last, i));
				last = i + 1;
				a++;
				break;
			}
		}
		result.format = s.substr(last, s.size());
	}
	return result;
}

