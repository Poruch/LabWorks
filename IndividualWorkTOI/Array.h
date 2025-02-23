#pragma once
#include <string>
#include "MyRecord.h"
#define ARRAY Arrays::MyArray


namespace Arrays {

	struct MyArray {
	public:

		MyArray();
		MyArray(int len);
		MyArray(const MyArray& array);
		static MyArray GetRandom(int length);
		static MyArray GetArrayFromFile(std::string fileName);
		static MyArray GetArrayFromConsole();
		void Reconstruct();

		void WriteArray();
		void WriteArray(int* indexes);
		void Sort(MyTypes::Criterion criterion, bool rise = true, bool quick = true);
		void Sort(int indStart,int indEnd, MyTypes::Criterion criterion, bool rise = true, bool quick = true);

		void SortIndexes(int** indexes, MyTypes::Criterion criterion, bool rise = true, bool quick = true);


		int Find(RECORD value);
		void DeleteFirstElem(RECORD value);

		void AddElem(RECORD value);

		void AddElems(int count);
		void AddElems(std::string fileName);
		
		void RecoverIndexes(bool rise = true);
		template <typename T>
		int FindAll(int** indexes, int* lenIndexes, T value, T (*criterion)(RECORD&)) {
			delete[](*indexes);
			int count = 0;
			(*indexes) = new int[length];
			for (int i = 0; i < length; i++) {
				if (criterion(records[i]) == value)
					(*indexes)[count++] = i;
			}
			if (count == 0)
				return -1;
			int* result = new int[count];
			for (int i = 0; i < count; i++) {
				result[i] = (*indexes)[i];
			}
			delete[](*indexes);
			(*indexes) = result;
			*lenIndexes = count;
			return 1;
		}

		template <typename T>
		int FindBinary(int* indexes,T value, T(*criterion)(RECORD&)) {
			int offsetLeft = 0;
			int offsetRight = length - 1;
			while (offsetLeft <= offsetRight) {
				int m = (offsetLeft + offsetRight) / 2;
				if (criterion(records[indexes[m]]) < value)
					offsetLeft = m + 1;
				else if (criterion(records[indexes[m]]) > value)
					offsetRight = m - 1;
				else
					return indexes[m];
			}
			return -1;
		}

		template <typename T>
		int FindBinary(int* indexes,T value, T(*criterion)(RECORD&), int offsetLeft, int offsetRight) {
			int m = (offsetLeft + offsetRight) / 2;
			if (offsetLeft > offsetRight)
				return -1;
			if (criterion(records[indexes[m]]) < value)
				return FindBinary(value, criterion, m + 1, offsetRight);
			else if (criterion(records[indexes[m]]) > value)
				return FindBinary(value, criterion, offsetLeft, m - 1);
			else
				return indexes[m];
		}

		
		template <typename T>
		int Find(T value, T(*criterion)(RECORD&)) {
			for (int i = 0; i < length; i++)
				if (criterion(records[i]) == value)
					return i;
			return -1;
		}

		template <typename T>
		void DeleteElems(T value, T(*criterion)(RECORD&)) {
			int* indexes = 0;
			int lenIndexes = 0;
			if (!(FindAll<T>(&indexes, &lenIndexes, value, criterion) + 1))
				return;
			int count = 0;
			RECORD* result = new RECORD[length - lenIndexes];
			for (int i = 0; i < length; i++) {
				if (i == indexes[count]) {
					count++;
				}
				else {
					result[i - count] = records[i];
				}
			}
			delete[] records;
			delete[] indexes;
			records = result;
			length -= lenIndexes;
			RecoverIndexes();
		}

		template <typename T>
		void DeleteFirstElem(T value, T(*criterion)(RECORD&)) {
			int ind = Find<T>(value, criterion);
			if (ind == -1)
				return;
			RECORD* result = new RECORD[length - 1];
			int j = 0;
			for (int i = 0; i < ind; i++)
			{
				result[j++] = records[i];
			}
			for (int i = ind + 1; i < length; i++)
			{
				result[j++] = records[i];
			}
			delete[] records;
			records = result;
			length -= 1;
			RecoverIndexes();
		}
		
		void DeleteWithNumber(int value) {
			int ind = value - 1;
			InBorder(ind);
			RECORD* result = new RECORD[length - 1];
			int j = 0;
			for (int i = 0; i < ind; i++)
			{
				result[j++] = records[i];
			}
			for (int i = ind + 1; i < length; i++)
			{
				result[j++] = records[i];
			}
			delete[] records;
			records = result;
			length -= 1;
			RecoverIndexes();
		}
		RECORD& operator[](int index) {
			InBorder(index);
			return records[index];
		}
		size_t Count() const {
			return length;
		};

		RECORD* GetData() {
			return records;
		}
		void DeleteData() {
			delete[] records;
			records = new RECORD[0];
			length = 0;
		}
	private:
		RECORD* records;
		size_t length;

		void GetSortIndexes(int* indexes, int(*criterion)(RECORD&), bool rise = true);
		void QuickGetSortIndexes(int* indexes, int len, int(*criterion)(RECORD&), bool rise);

		void QuickSort(RECORD* array, int len, int(*criterion)(RECORD&), bool rise = true);
		void ReSize(size_t newLen);

		void InBorder(int index) {
			if (index < 0 || index >= length) {
				throw "Выход за границу массива";
			}
		}
	};
}