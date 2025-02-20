#pragma once
#include <string>
#include <iostream>
#define RECORD MyTypes::Image

namespace MyTypes {
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
			std::cout << name.substr(0,6) << "\t";
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

	int static criterionName(RECORD& value) {
		return (int)value.name[0];
	}
	int static criterionHeight(RECORD& value) {
		return (int)value.height;
	}
	int static criterionWidth(RECORD& value) {
		return (int)value.width;
	}
	int static criterionColorDepth(RECORD& value) {
		return (int)value.colorDepth;
	}
	int static criterionSize(RECORD& value) {
		return (int)value.size;
	}
	int static criterionFormat(RECORD& value) {
		return (int)value.format[0];
	}
	int (* const criterions[6])(RECORD&) = { criterionName, criterionSize, criterionWidth, criterionHeight, criterionColorDepth, criterionFormat };
};
