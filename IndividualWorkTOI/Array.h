#include <string>

namespace MyTypes {
	struct Image;
}
namespace Arrays {
	void GetArrayFromFile(MyTypes::Image** arr,int* len, std::string fileName);
	void GetArray(MyTypes::Image** arr, int len);
	void Reconstruct(MyTypes::Image* arr, int len);

	void WriteArray(MyTypes::Image* arr, int len);

	void SortArray(MyTypes::Image* arr, int len, int (*criterion)(MyTypes::Image), bool rise = true);

	void GetSortIndexes(MyTypes::Image* arr, int** indexes, int len, int (*criterion)(MyTypes::Image), bool rise = true);
	void GetSortIndexes(MyTypes::Image* arr, int** indexes, int len, std::string (*criterion)(MyTypes::Image), bool rise = true);

	int FindAll(MyTypes::Image* arr, int** indexes, int* lenIndexes, int len, int value, int (*criterion)(MyTypes::Image));
	int FindAll(MyTypes::Image* arr, int** indexes,int* lenIndexes, int len, std::string value, std::string(*criterion)(MyTypes::Image));

	int FindBinary(MyTypes::Image* arr, int len, int value, int(*criterion)(MyTypes::Image));
	int FindBinary(MyTypes::Image* arr, int len, int value, int(*criterion)(MyTypes::Image), int leftOffset, int rightOffset);
	int FindBinary(MyTypes::Image* arr, int len, std::string value, std::string(*criterion)(MyTypes::Image));
	int FindBinary(MyTypes::Image* arr, int len, std::string value, std::string(*criterion)(MyTypes::Image), int leftOffset, int rightOffset);

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


}