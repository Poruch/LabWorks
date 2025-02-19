#pragma once
#include "Array.h"
#include <string>
#define ARRAY Arrays::MyArray
namespace HashTables {

	struct HashTable {
	public:
		HashTable(size_t size) {
			length = size;
			records = ARRAY(size);
			keys = new std::string[size];
			for (size_t i = 0; i < length; i++)
			{
				records[i] = RECORD();
				keys[i] = "";
			}
		}

		RECORD GetValue(std::string key) {
			int hash = GetHash(key);
			int count = 1;
			while (keys[hash] != key && count != length) {
				hash++;
				count++;
				hash = hash % length;
			}
			if (count == length)
				return RECORD();
			return records[hash];
		}

		void AddPair(std::string key, RECORD value) {
			int hash = GetHash(key);
			int count = 1;
			while (keys[hash] != "" && count != length) {
				hash++;
				count++;
				hash = hash % length;
			}
			if (keys[hash] == key) {
				return;
			}
			records[hash] = value;
			keys[hash] = key;
		}
	private:
		int GetHash(std::string key) {
			int sum = 0;
			for (int i = 0; i < key.length(); i++) {
				sum += abs(key[i]);
			}

			int hash = sum % length;
			return hash;
		}


		size_t length;
		ARRAY records;
		std::string* keys;
	};
}