#include "Array.h"

struct HashTable {
public:
	HashTable();
	HashTable(size_t size);

	void AddPair(std::string key,RECORD value) {

	}
private:
	int GetHash(std::string key) {
		int sum = 0;
		for (int i = 0; i < key.length(); i++) {
			sum += key[i];
		}
		int hash = sum % 10;
	}

	Arrays::MyArray records;
	std::string keys;
};