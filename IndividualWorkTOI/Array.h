#include <string>

#define RECORD MyTypes::Image
namespace MyTypes {
	struct Image;
}
namespace Arrays {

	struct MyArray {
	public:

		MyArray() {

		}
		void static GetArrayFromFile(MyTypes::Image** arr, int* len, std::string fileName);
		void GetArray(RECORD** arr, int len);
		void Reconstruct(RECORD* arr, int len);

		void WriteArray(RECORD* arr, int len);

		void SortArray(RECORD* arr, int len, int (*criterion)(RECORD), bool rise = true);

		void GetSortIndexes(RECORD* arr, int** indexes, int len, int (*criterion)(MyTypes::Image), bool rise = true);
		void GetSortIndexes(RECORD* arr, int** indexes, int len, std::string(*criterion)(MyTypes::Image), bool rise = true);

		int FindAll(RECORD* arr, int** indexes, int* lenIndexes, int len, int value, int (*criterion)(MyTypes::Image));
		int FindAll(RECORD* arr, int** indexes, int* lenIndexes, int len, std::string value, std::string(*criterion)(MyTypes::Image));

		int FindBinary(RECORD* arr, int len, int value, int(*criterion)(RECORD));
		int FindBinary(RECORD* arr, int len, int value, int(*criterion)(RECORD), int leftOffset, int rightOffset);
		int FindBinary(RECORD* arr, int len, std::string value, std::string(*criterion)(MyTypes::Image));
		int FindBinary(RECORD* arr, int len, std::string value, std::string(*criterion)(MyTypes::Image), int leftOffset, int rightOffset);

		int Find(MyTypes::Image* arr, int len, MyTypes::Image value);
		int Find(MyTypes::Image* arr, int len, int value, int(*criterion)(MyTypes::Image));
		int Find(MyTypes::Image* arr, int len, std::string value, std::string(*criterion)(MyTypes::Image));

		void DeleteElems(MyTypes::Image** arr, int* len, int value, int(*criterion)(MyTypes::Image));
		void DeleteElems(MyTypes::Image** arr, int* len, std::string value, std::string(*criterion)(MyTypes::Image));

		void DeleteFirstElem(MyTypes::Image** arr, int* len, int value, int(*criterion)(MyTypes::Image));
		void DeleteFirstElem(MyTypes::Image** arr, int* len, std::string value, std::string(*criterion)(MyTypes::Image));
		void DeleteFirstElem(MyTypes::Image** arr, int* len, MyTypes::Image value);

		void AddElem(MyTypes::Image** arr, int* len, MyTypes::Image value);
		void AddElems(MyTypes::Image** arr, int* len, int count);
		void AddElems(MyTypes::Image** arr, int* len, std::string fileName);

		void RecoverIndexes(MyTypes::Image* arr, int len, bool rise = true);
	private:
		RECORD records;

		void ReSize();
	};
	


}