#pragma once
#include <string>
#include "MyRecord.h"
namespace DataManage {
	class InputManager {
	public:
		static RECORD GetRecord(int from, std::string line = "", char separator = ' ');
		static RECORD GetRandomRecord();

		static std::string randomStrGen(int length) {
			static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
			std::string result;
			result.resize(length);
			for (int i = 0; i < length; i++)
				result[i] = charset[rand() % charset.length()];

			return result;
		}
	};
}
