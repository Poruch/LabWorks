#pragma once
#include <string>
#include <iostream>
#define RECORD MyTypes::Image

namespace MyTypes {
	struct Image;
	static unsigned int criterionName(RECORD& value);
	struct Image {
		
	public:
		
		size_t number;
		std::string name;
		unsigned int size;
		unsigned short width;
		unsigned short height;
		unsigned char colorDepth;
		std::string format;

		void Write() {
			std::cout << number << "\t";
			std::cout << name.substr(0, 6) << "\t";//"(" << std::to_string(criterionName(*this)) << ")" << "\t";
			std::cout << size << "\t";
			std::cout << width << "\t";
			std::cout << height << "\t";
			std::cout << (int)colorDepth << "\t";
			std::cout << format.substr(0, 6) << "\t";
		}
		Image(const Image& record)
			: number(record.number), 
			name(record.name), 
			size(record.size), 
			width(record.width), 
			height(record.height), 
			colorDepth(record.colorDepth), 
			format(record.format) {	}

		Image(int number, const std::string& name, int size, int width, int height, int colorDepth, const std::string& format)
			: number(number),
			name(name), 
			size(size), 
			width(width),
			height(height),
			colorDepth(colorDepth), 
			format(format) {	}

		Image(): number(0), name(""), size(0), width(0), height(0), colorDepth(0), format("")
		{
		}

		bool operator ==(Image im1) {
			return (name == im1.name) && (size == im1.size) && (width == im1.width) && (height == im1.height) && (colorDepth == im1.colorDepth) && (format == im1.format);
		}
		bool operator !=(Image im1) {
			return !operator==(im1);
		}				
		
	};
	static unsigned int GetIntFromString(std::string line) {
		size_t result = 0;
		int j = 0;
		for (int i = 0; i < (3 < line.size() ? 3 : line.size()); i++) {
			result += (line[i] + 255) * pow(10, 6 - (i + j++));
		}
		return (result);
	}
	typedef unsigned int (*Criterion)(RECORD&);
	unsigned int static criterionName(RECORD& value) {
		return GetIntFromString(value.name);
	}

	unsigned int static criterionHeight(RECORD& value) {
		return (unsigned int)value.height;
	}
	unsigned int static criterionWidth(RECORD& value) {
		return (unsigned int)value.width;
	}
	unsigned int static criterionColorDepth(RECORD& value) {
		return (unsigned int)value.colorDepth;
	}
	unsigned int static criterionSize(RECORD& value) {
		return (unsigned int)value.size;
	}
	unsigned int static criterionFormat(RECORD& value) {
		return (unsigned int)value.format[0];
	}
	static Criterion criterions[6] = { criterionName, criterionSize, criterionWidth, criterionHeight, criterionColorDepth, criterionFormat };
};