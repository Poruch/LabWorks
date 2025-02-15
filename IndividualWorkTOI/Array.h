#include <string>

#define RECORD MyTypes::Image
namespace MyTypes {
	struct Image;
}
namespace Arrays {

	struct MyArray {
	public:

		MyArray();
		MyArray(int len);
		~MyArray();

		static MyArray GetArrayFromFile(std::string fileName);
		
		void Reconstruct();

		void WriteArray();

		void SortArray(int (*criterion)(RECORD), bool rise = true);

		template <typename T>
		void GetSortIndexes(int** indexes, T(*criterion)(RECORD), bool rise = true);

		template <typename T>
		int FindAll(int** indexes, int* lenIndexes, T value, T (*criterion)(RECORD)) {
			delete[](*indexes);
			int count = 0;
			(*indexes) = new int[len];
			for (int i = 0; i < len; i++) {
				if (criterion(arr[i]) == value)
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

		}

		template <typename T>
		int FindBinary(T value, T(*criterion)(RECORD), int leftOffset, int rightOffset) {

		}

		int Find(RECORD value);

		template <typename T>
		int Find(T value, T(*criterion)(RECORD)) {
			for (int i = 0; i < len; i++)
				if (criterion(arr[i]) == value)
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
			RECORD* result = new RECORD[*len - lenIndexes];
			for (int i = 0; i < *len; i++) {
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
		void DeleteFirstElem(RECORD value);

		void AddElem(RECORD value);

		void AddElems(std::string fileName);

		void RecoverIndexes(bool rise = true);

		RECORD& operator[](int index) {
			InBorder(index);
			return records[index];
		}

		int Count() const {
			return length;
		};
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