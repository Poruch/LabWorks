#pragma once
#include <string>

namespace MyTypes {
	struct Image;
}
namespace DataManage {
	class InputManager {
	public:
		static MyTypes::Image GetRecord(int from, std::string line = "", char separator = ' ');
	};
}
