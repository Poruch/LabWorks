#include <string>
#include "MyRecord.h"
#define RECORD MyTypes::Image
namespace MyTypes {
	struct Image;
}
namespace Arrays {

	struct MyArray {
	public:

		MyArray();
		MyArray(int len);
		MyArray(const MyArray& array);
		~MyArray();
		
		static MyArray GetArrayFromFile(std::string fileName);
		
		void Reconstruct();

		void WriteArray();

		void Sort(int(*criterion)(RECORD), bool rise = true);
		void QuickSort(int(*criterion)(RECORD), bool rise = true);
		
		void GetSortIndexes(int** indexes, int(*criterion)(RECORD), bool rise = true);

		int Find(RECORD value);
		void DeleteFirstElem(RECORD value);

		void AddElem(RECORD value);

		void AddElems(int count);
		void AddElems(std::string fileName);

		void RecoverIndexes(bool rise = true);
		template <typename T>
		int FindAll(int** indexes, int* lenIndexes, T value, T (*criterion)(RECORD)) {
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
		int FindBinary(T value, T(*criterion)(RECORD)) {
			int offsetLeft = 0;
			int offsetRight = length - 1;
			while (offsetLeft <= offsetRight) {
				int m = (offsetLeft + offsetRight) / 2;
				if (criterion(records[m]) < value)
					offsetLeft = m + 1;
				else if (criterion(records[m]) > value)
					offsetRight = m - 1;
				else
					return m;
			}
			return -1;
		}

		template <typename T>
		int FindBinary(T value, T(*criterion)(RECORD), int offsetLeft, int offsetRight) {
			int m = (offsetLeft + offsetRight) / 2;
			if (offsetLeft > offsetRight)
				return -1;
			if (criterion(records[m]) < value)
				return FindBinary(value, criterion, m + 1, offsetRight);
			else if (criterion(records[m]) > value)
				return FindBinary(value, criterion, offsetLeft, m - 1);
			else
				return m;
		}

		
		template <typename T>
		int Find(T value, T(*criterion)(RECORD)) {
			for (int i = 0; i < length; i++)
				if (criterion(records[i]) == value)
					return i;
			return -1;
		}

		template <typename T>
		void DeleteElems(T value, T(*criterion)(RECORD)) {
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
		void DeleteFirstElem(T value, T(*criterion)(RECORD)) {
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
		

		RECORD& operator[](int index) {
			InBorder(index);
			return records[index];
		}

		int Count() const {
			return length;
		};

		RECORD* GetData() {
			return records;
		}
	private:
		RECORD* records;
		size_t length;

		void ReSize(size_t newLen);
		void InBorder(int index) {
			if (index < 0 || index >= length) {
				throw "Выход за границу массива";
			}
		}
	};
}