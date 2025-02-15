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

		MyArray GetArrayFromFile(MyTypes::Image** arr, int* len, std::string fileName);
		
		void Reconstruct();

		void WriteArray();

		void SortArray(int (*criterion)(RECORD), bool rise = true);

		void GetSortIndexes(int** indexes, int (*criterion)(MyTypes::Image), bool rise = true);
		void GetSortIndexes(int** indexes, std::string(*criterion)(MyTypes::Image), bool rise = true);

		int FindAll(int** indexes, int* lenIndexes, int value, int (*criterion)(MyTypes::Image));
		int FindAll(int** indexes, int* lenIndexes, std::string value, std::string(*criterion)(MyTypes::Image));

		int FindBinary(int value, int(*criterion)(RECORD));
		int FindBinary(int value, int(*criterion)(RECORD), int leftOffset, int rightOffset);
		int FindBinary(std::string value, std::string(*criterion)(MyTypes::Image));
		int FindBinary(std::string value, std::string(*criterion)(MyTypes::Image), int leftOffset, int rightOffset);

		int Find(MyTypes::Image value);
		int Find(int value, int(*criterion)(MyTypes::Image));
		int Find(std::string value, std::string(*criterion)(MyTypes::Image));

		void DeleteElems(int value, int(*criterion)(MyTypes::Image));
		void DeleteElems(std::string value, std::string(*criterion)(MyTypes::Image));

		void DeleteFirstElem(int value, int(*criterion)(MyTypes::Image));
		void DeleteFirstElem(std::string value, std::string(*criterion)(MyTypes::Image));
		void DeleteFirstElem(MyTypes::Image value);

		void AddElem(MyTypes::Image value);
		void AddElems(int count);
		void AddElems(std::string fileName);

		void RecoverIndexes(bool rise = true);

		RECORD operator[](int index) {

		}

		int Count() const {
			return length;
		};
	private:
		RECORD* records;
		size_t length;


		void ReSize();
	};
}