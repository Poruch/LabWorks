#pragma once
#include <string>

namespace MyTypes {
	struct Image;
}
namespace DataManage {
	class InputManager {
	public:
		static MyTypes::Image GetRecord();
		static MyTypes::Image GetRecord(std::string line);
	};
}
