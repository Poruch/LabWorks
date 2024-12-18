#pragma once
#include <string>
#include <iostream>
namespace MyTypes {
	struct Image {
	public:
		int number;
		std::string name;
		int size;
		int width;
		int height;
		int colorDepth;
		std::string format;
		void Write() {

			std::cout << number << "\t";
			std::cout << name << "\t";
			std::cout << size << "\t";
			std::cout << width << "\t";
			std::cout << height << "\t";
			std::cout << colorDepth << "\t";
			std::cout << format << "\t";
		}
	};
}