#include <string>


namespace MyTypes {
struct Image;
void GetArrayFromFile(Image** arr,int* len, std::string fileName);


void GetArray(Image** arr, int len);

void WriteArray(Image* arr, int len);
void SortArray(Image* arr, int len, int (*criterion)(Image));
void FindElem(Image* arr, int len, Image image, int idCriterion);
void DeleteElem(Image** arr, int len, Image image, int idCriterion);
}