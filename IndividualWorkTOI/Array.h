#include <string>


namespace MyTypes {
struct Image;

	void GetArrayFromFile(Image** arr,int* len, std::string fileName);


	void GetArray(Image** arr, int len);

	void WriteArray(Image* arr, int len);
	void SortArray(Image* arr, int len, int (*criterion)(Image), bool rise = true);

	int FindBinary(Image* arr, int len, int value, int(*criterion)(Image));
	int FindBinary(Image* arr, int len, std::string value, std::string(*criterion)(Image));
	int Find(Image* arr, int len, Image value);

	int DeleteElems(Image** arr, int len, int value, int(*criterion)(Image));
	int DeleteElems(Image** arr, int len, std::string value, std::string(*criterion)(Image));

	int DeleteFirstElem(Image** arr, int len, int value, int(*criterion)(Image));
	int DeleteFirstElem(Image** arr, int len, std::string value, std::string(*criterion)(Image));


	int DeleteFirstElem(Image** arr, int len, Image value);
}