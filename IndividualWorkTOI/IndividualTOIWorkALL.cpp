#include <string>
#include <fstream>
#include <iostream>
#define RECORD MyTypes::Image

namespace MyTypes {
	struct Image {
	public:


		size_t number;
		std::string name;
		unsigned int size;
		unsigned short width;
		unsigned short height;
		unsigned char colorDepth;
		std::string format;

		void Write() {
			std::cout << number << "\t";
			std::cout << name.substr(0, 6) << "\t";
			std::cout << size << "\t";
			std::cout << width << "\t";
			std::cout << height << "\t";
			std::cout << (int)colorDepth << "\t";
			std::cout << format.substr(0, 6) << "\t";
		}
		Image(const Image& record)
			: number(record.number),
			name(record.name),
			size(record.size),
			width(record.width),
			height(record.height),
			colorDepth(record.colorDepth),
			format(record.format) {
		}

		Image(int number, const std::string& name, int size, int width, int height, int colorDepth, const std::string& format)
			: number(number),
			name(name),
			size(size),
			width(width),
			height(height),
			colorDepth(colorDepth),
			format(format) {
		}

		Image() : number(0), name(""), size(0), width(0), height(0), colorDepth(0), format("")
		{
		}

		bool operator ==(Image im1) {
			return (name == im1.name) && (size == im1.size) && (width == im1.width) && (height == im1.height) && (colorDepth == im1.colorDepth) && (format == im1.format);
		}
		bool operator !=(Image im1) {
			return !operator==(im1);
		}

	};
	typedef int (*Criterion)(RECORD&);
	int static criterionName(RECORD& value) {
		int result = 0;
		for (int i = 0; i < value.name.length(); i++) {
			result += ((char)value.name[i]) * pow(10, value.name.length() - i);
		}
		return result / (pow(10, value.name.length() / 2));
	}
	int static criterionHeight(RECORD& value) {
		return (int)value.height;
	}
	int static criterionWidth(RECORD& value) {
		return (int)value.width;
	}
	int static criterionColorDepth(RECORD& value) {
		return (int)value.colorDepth;
	}
	int static criterionSize(RECORD& value) {
		return (int)value.size;
	}
	int static criterionFormat(RECORD& value) {
		return (int)value.format[0];
	}
	static Criterion criterions[6] = { criterionName, criterionSize, criterionWidth, criterionHeight, criterionColorDepth, criterionFormat };
};
namespace DataManage {
	class InputManager {
	public:
		static RECORD GetRecord(int from, std::string line = "", char separator = ' ');
		static RECORD GetRandomRecord();

		static std::string randomStrGen(int length) {
			static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
			std::string result;
			result.resize(length);
			for (int i = 0; i < length; i++)
				result[i] = charset[rand() % charset.length()];

			return result;
		}
	};
}
MyTypes::Image DataManage::InputManager::GetRecord(int from, std::string line, char separator) {
	MyTypes::Image result = MyTypes::Image();
	if (from & 1)
		std::getline(std::cin, line);
	int last = 0;
	int a = -1;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == separator) {
			switch (a)
			{
			case -1:
				result.number = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 0:
				result.name = line.substr(last, i - last);
				last = i + 1;
				a++;
				break;
			case 1:
				result.size = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 2:
				result.width = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 3:
				result.height = stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			case 4:
				result.colorDepth = (unsigned char)stoi(line.substr(last, i - last));
				last = i + 1;
				a++;
				break;
			}
		}
		result.format = line.substr(last, line.size() - last);
	}
	return result;
}

MyTypes::Image DataManage::InputManager::GetRandomRecord() {
	MyTypes::Image result = MyTypes::Image();
	result.name = randomStrGen(5);
	result.size = rand() % (1000 - 10 + 1) + 10;
	result.width = rand() % (5000 - 10 + 1) + 10;
	result.height = rand() % (5000 - 10 + 1) + 10;
	result.colorDepth = pow(2, rand() % (8 - 1 + 1) + 1);
	result.format = randomStrGen(3);
	return result;
}


#define ARRAY Arrays::MyArray
namespace MyTypes {
	struct Image {

	public:


		size_t number;
		std::string name;
		unsigned int size;
		unsigned short width;
		unsigned short height;
		unsigned char colorDepth;
		std::string format;

		void Write() {
			std::cout << number << "\t";
			std::cout << name.substr(0, 6) << "\t";
			std::cout << size << "\t";
			std::cout << width << "\t";
			std::cout << height << "\t";
			std::cout << (int)colorDepth << "\t";
			std::cout << format.substr(0, 6) << "\t";
		}
		Image(const Image& record)
			: number(record.number),
			name(record.name),
			size(record.size),
			width(record.width),
			height(record.height),
			colorDepth(record.colorDepth),
			format(record.format) {
		}

		Image(int number, const std::string& name, int size, int width, int height, int colorDepth, const std::string& format)
			: number(number),
			name(name),
			size(size),
			width(width),
			height(height),
			colorDepth(colorDepth),
			format(format) {
		}

		Image() : number(0), name(""), size(0), width(0), height(0), colorDepth(0), format("")
		{
		}

		bool operator ==(Image im1) {
			return (name == im1.name) && (size == im1.size) && (width == im1.width) && (height == im1.height) && (colorDepth == im1.colorDepth) && (format == im1.format);
		}
		bool operator !=(Image im1) {
			return !operator==(im1);
		}

	};
	typedef int (*Criterion)(RECORD&);
	int static criterionName(RECORD& value) {
		int result = 0;
		for (int i = 0; i < value.name.length(); i++) {
			result += ((char)value.name[i]) * pow(10, value.name.length() - i);
		}
		return result / (pow(10, value.name.length() / 2));
	}
	int static criterionHeight(RECORD& value) {
		return (int)value.height;
	}
	int static criterionWidth(RECORD& value) {
		return (int)value.width;
	}
	int static criterionColorDepth(RECORD& value) {
		return (int)value.colorDepth;
	}
	int static criterionSize(RECORD& value) {
		return (int)value.size;
	}
	int static criterionFormat(RECORD& value) {
		return (int)value.format[0];
	}
	static Criterion criterions[6] = { criterionName, criterionSize, criterionWidth, criterionHeight, criterionColorDepth, criterionFormat };
};

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
		void Sort(int indStart, int indEnd, MyTypes::Criterion criterion, bool rise = true, bool quick = true);

		void SortIndexes(int** indexes, MyTypes::Criterion criterion, bool rise = true, bool quick = true);


		int Find(RECORD value);
		void DeleteFirstElem(RECORD value);

		void AddElem(RECORD value);

		void AddElems(int count);
		void AddElems(std::string fileName);

		void RecoverIndexes(bool rise = true);
		template <typename T>
		int FindAll(int** indexes, int* lenIndexes, T value, T(*criterion)(RECORD&)) {
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
		int FindBinary(int* indexes, T value, T(*criterion)(RECORD&)) {
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
		int FindBinary(int* indexes, T value, T(*criterion)(RECORD&), int offsetLeft, int offsetRight) {
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

		void DeleteWithNumber(int value);
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
				throw "����� �� ������� �������";
			}
		}
	};
}

#include <vector>

#define CONSOLE 1
#define FILE  2

namespace Arrays {
	MyArray::MyArray()
	{
		length = 0;
		records = 0;
	}
	MyArray::MyArray(int len)
	{
		length = len;
		records = new RECORD[len];
	}
	MyArray::MyArray(const MyArray& array)
	{
		length = array.length;
		records = array.records;
	}

	MyArray MyArray::GetRandom(int length)
	{
		MyArray result(length);
		for (size_t i = 0; i < length; i++)
		{

			result[i] = DataManage::InputManager::GetRandomRecord();
			result[i].number = i + 1;
		}
		return result;
	}

	MyArray MyArray::GetArrayFromFile(std::string fileName) {
		std::ifstream file(fileName);
		int len = 0;
		std::string s;
		if (file.is_open()) {
			while (std::getline(file, s)) {
				(len)++;
			}
		}
		else
			return MyArray();
		file.close();
		file = std::ifstream(fileName);
		MyArray result(len);
		if (len == 0)
			throw "�� ������� ������� ����";
		int i = 0;
		while (i < len) {
			std::getline(file, s);
			result[i] = DataManage::InputManager::GetRecord(FILE, s, '\t');
			i++;
		}
		file.close();
		return result;
	}

	MyArray MyArray::GetArrayFromConsole()
	{
		std::cout << "������� ����� �������" << "\n";
		std::string line = "";
		std::getline(std::cin, line);
		int length = std::stoi(line);
		MyArray result(length);
		for (size_t i = 0; i < length; i++)
		{
			result[i] = DataManage::InputManager::GetRecord(CONSOLE);
			result[i].number = i + 1;
		}
		return result;
	}

	void MyArray::WriteArray() {
		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
		for (int i = 0; i < length; i++) {
			records[i].Write();
			std::cout << "\n";
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	void MyArray::WriteArray(int* indexes) {
		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
		for (int i = 0; i < length; i++) {
			records[indexes[i]].Write();
			std::cout << "\n";
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	void MyArray::Reconstruct() {
		for (int i = 0; i < length; i++) {
			RECORD buff = records[records[i].number - 1];
			records[records[i].number - 1] = records[i];
			records[i] = buff;
		}
	}
	void MyArray::Sort(int indStart, int indEnd, MyTypes::Criterion criterion, bool rise, bool quick) {
		if (!quick)
			for (int i = indStart; i < indEnd - 1; i++) {
				for (int j = i + 1; j < indEnd; j++) {
					if (criterion(records[i]) > criterion(records[j]) == rise) {
						auto buff = records[i];
						records[i] = records[j];
						records[j] = buff;
					}
				}
			}
		else {
			QuickSort(records + indStart, indEnd - indStart, criterion, rise);
		}
	}
	void MyArray::Sort(MyTypes::Criterion criterion, bool rise, bool quick) {
		if (!quick)
			for (int i = 0; i < length - 1; i++) {
				for (int j = i + 1; j < length; j++) {
					if (criterion(records[i]) > criterion(records[j]) == rise) {
						auto buff = records[i];
						records[i] = records[j];
						records[j] = buff;
					}
				}
			}
		else {
			QuickSort(records, length, criterion, rise);
		}
	}

	void MyArray::DeleteWithNumber(int value) {
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

	void MyArray::QuickSort(RECORD* array, int len, int(*criterion)(RECORD&), bool rise) {
		int i = 0;
		int j = len - 1;
		int mid = criterion(array[len / 2]);
		do {
			if (rise) {
				while (criterion(array[i]) < mid) {
					i++;
				}
				while (criterion(array[j]) > mid) {
					j--;
				}
				if (i <= j) {
					RECORD tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					i++;
					j--;
				}
			}
			else {
				while (criterion(array[i]) > mid) {
					i++;
				}
				while (criterion(array[j]) < mid) {
					j--;
				}
				if (i <= j) {
					RECORD tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					i++;
					j--;
				}
			}
		} while (i <= j);
		if (j > 0) {
			QuickSort(array, j + 1, criterion, rise);
		}
		if (i < len) {
			QuickSort(&array[i], len - i, criterion, rise);
		}
	}

	void MyArray::GetSortIndexes(int* indexes, MyTypes::Criterion criterion, bool rise) {
		for (int i = 0; i < length - 1; i++) {
			for (int j = i + 1; j < length; j++) {
				if ((criterion(records[indexes[i]]) > criterion(records[indexes[j]])) == rise) {
					auto buff = indexes[i];
					indexes[i] = indexes[j];
					indexes[j] = buff;
				}
			}
		}
	}

	void MyArray::SortIndexes(int** indexes, MyTypes::Criterion criterion, bool rise, bool quick) {
		delete[](*indexes);
		(*indexes) = new int[Count()];
		for (int i = 0; i < Count(); i++) {
			(*indexes)[i] = i;
		}
		if (quick) {
			QuickGetSortIndexes((*indexes), Count(), criterion, rise);
		}
		else {
			GetSortIndexes((*indexes), criterion, rise);
		}
	}

	void MyArray::QuickGetSortIndexes(int* indexes, int len, MyTypes::Criterion criterion, bool rise) {
		int i = 0;
		int j = len - 1;
		int mid = criterion(records[indexes[len / 2]]);
		do {
			if (rise) {
				while (criterion(records[indexes[i]]) < mid) {
					i++;
				}
				while (criterion(records[indexes[j]]) > mid) {
					j--;
				}
				if (i <= j) {
					int tmp = indexes[i];
					indexes[i] = indexes[j];
					indexes[j] = tmp;
					i++;
					j--;
				}
			}
			else {
				while (criterion(records[indexes[i]]) > mid) {
					i++;
				}
				while (criterion(records[indexes[j]]) < mid) {
					j--;
				}
				if (i <= j) {
					int tmp = indexes[i];
					indexes[i] = indexes[j];
					indexes[j] = tmp;
					i++;
					j--;
				}
			}
		} while (i <= j);
		if (j > 0) {
			QuickGetSortIndexes(indexes, j + 1, criterion, rise);
		}
		if (i < len) {
			QuickGetSortIndexes(&indexes[i], len - i, criterion, rise);
		}
	}
	int MyArray::Find(RECORD value) {
		for (int i = 0; i < length; i++)
			if (records[i] == value)
				return i;
		return -1;
	}

	void MyArray::RecoverIndexes(bool rise) {
		int* indexes = 0;
		SortIndexes(&indexes, [](RECORD& image) {return (int)image.number; }, rise);
		for (int i = 0; i < length; i++) {
			records[indexes[i]].number = i + 1;
		}
		delete[] indexes;
	}

	void MyArray::DeleteFirstElem(RECORD value) {
		int ind = Find(value);
		if (ind == -1)
			return;
		RECORD* currentArray = new RECORD[length - 1];
		int j = 0;
		for (int i = 0; i < ind; i++)
		{
			currentArray[j++] = records[i];
		}
		for (int i = ind + 1; i < length; i++)
		{
			currentArray[j++] = records[i];
		}
		delete[] records;
		records = currentArray;
		length -= 1;
		RecoverIndexes();
	}
	void MyArray::AddElem(RECORD value) {
		int newLen = 1 + length;
		ReSize(newLen);
		records[length] = value;
		length = newLen;
	}

	void MyArray::AddElems(int count) {
		int newLen = count + length;
		RECORD* result = new RECORD[newLen];

		for (int i = 0; i < length; i++) {
			result[i] = records[i];
		}
		for (int i = length; i < newLen; i++) {
			result[i] = DataManage::InputManager::GetRecord(CONSOLE);
		}
		delete[] records;

		records = result;
		length = newLen;
	}

	void MyArray::AddElems(std::string fileName) {
		MyArray addRecords = GetArrayFromFile(fileName);
		int newLen = addRecords.Count() + length;
		RECORD* result = new RECORD[newLen];
		int count = 1;
		for (int i = 0; i < length; i++) {
			result[i] = records[i];
			count++;
		}
		for (int i = 0; i < addRecords.Count(); i++) {
			result[i + length] = addRecords[i];
			result[i + length].number = count++;
		}
		delete[] records;

		records = result;
		length = newLen;
	}



	void MyArray::ReSize(size_t newLen) {
		RECORD* newRecords = new RECORD[newLen];
		for (int i = 0; i < length; i++) {
			newRecords[i] = records[i];
		}
		delete[] records;
		records = newRecords;
	}
}
#define LIST Lists::List
#define CRITERION(indCriterion) criterions[indCriterion]

namespace Lists {
	template<int N>
	struct List {
	private:

		struct Node
		{
			Node* nextNode;
			int index = 0;
			RECORD* record = 0;

			Node(int ind, RECORD* im) {
				nextNode = nullptr;
				index = ind;
				record = im;
			}
			Node() {
				nextNode = nullptr;
				index = 0;
				record = RECORD();
			}
			template <typename T>
			T GetValue(T(*criterion)(RECORD&)) {
				return criterion(*record);
			}

			bool operator==(const Node& node) {
				return record == node.record;
			}
			bool operator!=(const Node& node) {
				return !operator==(node);
			}
		};
	public:

		RECORD* Find(int value, int criterionInd) {
			Node* current = first[criterionInd + 1];
			while (current && current->GetValue(CRITERION(criterionInd)) != value) {
				current = current->nextNode;
			}
			if (current == nullptr)
				return new RECORD();
			return current->record;
		}


		List() {
			int (*criterionsForList[])(RECORD&) = { MyTypes::criterionName, MyTypes::criterionHeight };
			static_assert(N > 0 && N <= 6, "���������� ��������� ������ ���� ������ 0");
			for (size_t i = 0; i < N; i++) {
				criterions[i] = criterionsForList[i];
				first[i] = nullptr;
				last[i] = nullptr;
			}
			first[N] = nullptr;
			last[N] = nullptr;
			count = 0;
		}
		int criterionInds[N];
		List(int criterions[N]) {
			static_assert(N > 0 && N <= 6, "���������� ��������� ������ ���� ������ 0");
			for (size_t i = 0; i < N; i++) {
				this->criterions[i] = MyTypes::criterions[criterions[i]];
				criterionInds[i] = criterions[i];
				first[i] = nullptr;
				last[i] = nullptr;
			}
			first[N] = nullptr;
			last[N] = nullptr;
			count = 0;
		}

		bool IsEmpty() {
			bool result = true;
			for (int i = 0; i < N + 1; i++) {
				result = result && (first[i] == nullptr);
			}
			return result;
		}

		bool IsEmpty(int ind) {
			return first[ind] == nullptr;
		}

		void Push(RECORD* value) {
			count++;
			Node* newPointer = new Node(count, value);
			if (IsEmpty(0)) {
				first[0] = newPointer;
				last[0] = newPointer;
				for (int i = 0; i < N; i++) {
					SortedPush(value, i + 1);
				}
				return;
			}
			newPointer->nextNode = first[0];
			first[0] = newPointer;
			for (int i = 0; i < N; i++) {
				SortedPush(value, i + 1);
			}
		}

		int count = 0;
		int Count() { return count; }
		void PushBack(RECORD* value) {
			count++;
			Node* newPointer = new Node(count, value);
			if (IsEmpty(0)) {
				first[0] = newPointer;
				last[0] = newPointer;
				for (int i = 0; i < N; i++) {
					SortedPush(value, i + 1);
				}
				return;
			}
			last[0]->nextNode = newPointer;
			last[0] = newPointer;
			for (int i = 0; i < N; i++) {
				SortedPush(value, i + 1);
			}
		}



		Node* operator[] (const int index) {
			if (IsEmpty(0)) return nullptr;
			Node* current = first[0];
			for (int i = 0; i < index; i++) {
				current = current->nextNode;
				if (!current) return nullptr;
			}
			return current;
		}




		void ReverseIter(int IndCriterion) {
			last[IndCriterion] = first[IndCriterion];
			Node* buffer = GetReverseListIt(first[IndCriterion]);
			first[IndCriterion] = buffer;
		}
		void ReverseRec(int IndCriterion) {
			last[IndCriterion] = first[IndCriterion];
			Node* buffer = GetReverseListRec(first[IndCriterion]);
			first[IndCriterion] = buffer;
		}

		void Remove(int value, MyTypes::Criterion criterion) {
			if (IsEmpty(0)) return;

			if (first[0] == last[0]) {
				for (size_t i = 0; i < N + 1; i++) {
					delete first[i];
					first[i] = nullptr;
					last[i] = nullptr;
				}
				return;
			}

			if (first[0]->GetValue(criterion) == value) {
				RemoveFirst();
				return;
			}

			else if (last[0]->GetValue(criterion) == value) {
				RemoveLast();
				return;
			}

			Node* slow = first[0];
			Node* fast = first[0]->nextNode;
			while (fast && fast->GetValue(criterion) != value) {
				slow = fast;
				fast = fast->nextNode;
			}
			if (!fast) {
				std::cout << "This element does not exist" << std::endl;
				return;
			}
			RemoveNode(fast);
			slow->nextNode = fast->nextNode;
			delete fast;
		}

		void RemoveFirst() {
			if (IsEmpty(0))	return;
			Node* node = first[0];
			first[0] = first[0]->nextNode;
			RemoveNode(node);
			delete node;
		}

		void RemoveLast() {
			if (IsEmpty(0)) return;
			Node* current = first[0];
			while (current->nextNode != last[0]) {
				current = current->nextNode;
			}
			Node* node = last[0];
			last[0] = current;
			RemoveNode(node);
			delete node;
		}

		void DeleteWithNumber(int value) {
			if (IsEmpty(0)) return;

			if (first[0] == last[0]) {
				for (size_t i = 0; i < N + 1; i++) {
					delete first[i];
					first[i] = nullptr;
					last[i] = nullptr;
				}
				return;
			}

			if (first[0]->record->number == value) {
				RemoveFirst();
				return;
			}

			else if (last[0]->record->number == value) {
				RemoveLast();
				return;
			}

			Node* slow = first[0];
			Node* fast = first[0]->nextNode;
			while (fast && fast->record->number != value) {
				slow = fast;
				fast = fast->nextNode;
			}

			if (!fast) {
				std::cout << "This element does not exist" << std::endl;
				return;
			}
			RemoveNode(fast);
			slow->nextNode = fast->nextNode;
			delete fast;
		}

		void DeleteData() {
			if (IsEmpty(0))	return;
			count = 0;
			for (int i = 0; i < N + 1; i++) {
				Node* node = first[i];
				while (node != nullptr) {
					Node* deleted = node;
					node = node->nextNode;
					delete deleted;
				}
				last[i] = nullptr;
				first[i] = nullptr;
			}
		}

		void WriteList() {
			if (IsEmpty(0)) return;
			Node* current = first[0];

			std::cout << "////////////////////////////////////////////////////////////////\n";
			std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
			while (current != nullptr)
			{
				if (current->record)
					current->record->Write();
				std::cout << std::endl;
				current = current->nextNode;
				if (current) {
					std::cout << "|" << std::endl;
					std::cout << "V" << std::endl;
				}
			}
			std::cout << "////////////////////////////////////////////////////////////////\n";
		}
		void WriteList(int criterionInd, bool rise = true) {
			if (IsEmpty(criterionInd)) return;
			Node* current;
			if (!rise)
				ReverseRec(rise);
			current = first[criterionInd];

			if (criterionInd == 0) {
				WriteList();
				return;
			}

			std::cout << "////////////////////////////////////////////////////////////////\n";
			std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
			while (current)
			{
				if (current->record != NULL)
					current->record->Write();
				std::cout << std::endl;
				current = current->nextNode;
				if (current) {
					for (int i = 0; i < criterionInds[criterionInd - 1] + 1; i++)
						std::cout << "\t";
					std::cout << "|" << std::endl;
					for (int i = 0; i < criterionInds[criterionInd - 1] + 1; i++)
						std::cout << "\t";
					std::cout << "V" << std::endl;
				}
			}
			if (!rise)
				ReverseRec(criterionInd);
			std::cout << "////////////////////////////////////////////////////////////////\n";
		}
	private:
		void Push(RECORD* value, int indCriterion) {
			Node* newPointer = new Node(count, value);
			if (IsEmpty(indCriterion)) {
				first[indCriterion] = newPointer;
				last[indCriterion] = newPointer;
				return;
			}
			newPointer->nextNode = first[indCriterion];
			first[indCriterion] = newPointer;
		}
		void PushBack(RECORD* value, int indCriterion) {
			Node* newPointer = new Node(count, value);
			if (IsEmpty(indCriterion)) {
				first[indCriterion] = newPointer;
				last[indCriterion] = newPointer;
				return;
			}
			last[indCriterion]->nextNode = newPointer;
			last[indCriterion] = newPointer;
		}

		Node* GetReverseListIt(Node* root) {
			Node* new_root = 0;
			while (root) {
				Node* next = root->nextNode;
				root->nextNode = new_root;
				new_root = root;
				root = next;
			}
			return new_root;
		}

		Node* GetReverseListRec(Node* root) {
			if (root == nullptr || root->nextNode == nullptr)
				return root;
			Node* rest = GetReverseListRec(root->nextNode);
			root->nextNode->nextNode = root;
			root->nextNode = nullptr;
			return rest;
		}

		void RemoveNode(Node* node) {
			for (int i = 1; i < N + 1; i++) {

				if ((*first[i]) == (*node)) {
					RemoveFirstNode(i);
					continue;
				}

				else if ((*last[i]) == (*node)) {
					RemoveLastNode(i);
					continue;
				}

				Node* slow = first[i];
				Node* fast = first[i]->nextNode;

				while (fast && ((*fast) != (*node))) {
					slow = fast;
					fast = fast->nextNode;
				}

				slow->nextNode = fast->nextNode;
				delete fast;
			}
		}

		void RemoveFirstNode(int index) {
			if (IsEmpty(index))	return;
			Node* node = first[index];
			first[index] = first[index]->nextNode;
			delete node;
		}

		void RemoveLastNode(int index) {
			if (IsEmpty(index)) return;
			Node* current = first[index];
			while (current->nextNode != last[index]) {
				current = current->nextNode;
			}
			Node* node = last[index];
			last[index] = current;
			delete node;
		}

		void SortedPush(RECORD* value, int indCriterion) {
			int val = CRITERION(indCriterion - 1)(*value);
			Node* newPointer = new Node(count, value);
			if (IsEmpty(indCriterion)) {
				first[indCriterion] = newPointer;
				last[indCriterion] = newPointer;
				return;
			}
			if (val <= first[indCriterion]->GetValue(CRITERION(indCriterion - 1))) {
				Push(value, indCriterion);
				return;
			}
			if (val >= last[indCriterion]->GetValue(CRITERION(indCriterion - 1))) {
				PushBack(value, indCriterion);
				return;
			}
			Node* slow = first[indCriterion];
			Node* fast = first[indCriterion]->nextNode;

			while (fast && (val > fast->GetValue(CRITERION(indCriterion - 1)))) {
				slow = fast;
				fast = fast->nextNode;
			}

			slow->nextNode = newPointer;
			newPointer->nextNode = fast;
		}


		MyTypes::Criterion criterions[N];
		Node* first[N + 1];
		Node* last[N + 1];
	};
};

#define TREE Trees::BTree

namespace Trees {

	template<int N>
	struct BTree {
	private:
		struct BNode
		{
			RECORD** records;
			BNode* children[2 * N + 1];
			BNode* parent;

			int count;
			int countSons;
			bool leaf;

			BNode() : leaf(true) {
				records = new RECORD * [2 * N];
				for (int i = 0; i < 2 * N; i++) records[i] = nullptr;
				for (int i = 0; i <= 2 * N; i++) children[i] = nullptr;
				parent = nullptr;
				count = 0;
				countSons = 0;
			};

			BNode(bool isLeaf) : leaf(isLeaf) {
				records = new RECORD * [2 * N];
				for (int i = 0; i < 2 * N; i++) records[i] = nullptr;
				for (int i = 0; i <= 2 * N; i++) children[i] = nullptr;
				parent = nullptr;
				count = 0;
				countSons = 0;
			};

			int GetValue(int index, int (*criterion)(RECORD&)) {
				return criterion(*records[index]);
			}

			RECORD& operator[](int index) {
				return records[index];
			}
		};
		int (*criterion)(RECORD&);
		BNode* root;
	public:
		BTree(int criterionInd) {
			root = nullptr;
			this->criterion = MyTypes::criterions[criterionInd];
		}
		BTree(const BTree& tree) {
			root = tree.root;
		}
		BTree() {
			root = nullptr;
			this->criterion = MyTypes::criterionName;
		}
		~BTree() {
			if (root != nullptr)
				DeleteNode(root);
		}
		void DeleteData() {
			if (root != nullptr)
				DeleteNode(root);
		}
		RECORD Find(int value) {
			return GetRecordWhithKey(value, root);
		}

		bool Contains(int value) {
			return FindKey(value, root);
		}

		void Insert(RECORD& value) {
			if (IsEmpty()) {
				BNode* newRoot = new BNode();
				newRoot->records[0] = &value;
				newRoot->count++;
				root = newRoot;
			}
			else {
				BNode* current = root;
				while (!current->leaf) {
					for (int i = 0; i < 2 * N; i++) {
						if (current->records[i] != nullptr) {
							if (criterion(value) <= criterion((*current->records[i]))) {
								current = current->children[i];
								break;
							}
							if (((i + 1) == current->count || current->records[i + 1] == nullptr) && (criterion(value) > criterion((*current->records[i])))) {
								current = current->children[i + 1];
								break;
							}
						}
						else break;
					}
				}
				InsertToNode(value, current);

				while (current->count == 2 * N) {
					if (current == root) {
						Restruct(current);
						break;
					}
					else {
						Restruct(current);
						BNode* oldCurrent = current;
						current = current->parent;
						delete oldCurrent;
					}
				}
			}
		}

		void Delete(int value) {
			Remove(value, root);
		}

		void WriteTree(bool rise = true) {
			WriteNode(root, 0, rise);
		}
		void WriteTreeKeys(bool rise = true) {
			WriteKey(root, 0, rise);
		}

		bool IsEmpty() {
			return root == nullptr;
		}
	private:
		void WriteNode(BNode* node, int deep, bool rise = true) {
			if (node == nullptr) return;
			if (node->leaf) {
				if (rise)
					for (size_t i = 0; i < node->count; i++)
					{
						for (int i = 0; i < deep; i++)
							std::cout << "   ";
						node->records[i]->Write();
						std::cout << "\n";
					}
				else {
					for (size_t i = node->count - 1; i > 0; i--) {
						for (int j = 0; j < deep; j++)
							std::cout << "   ";
						node->records[i]->Write();
						std::cout << "\n";
					}
					for (int j = 0; j < deep; j++)
						std::cout << "   ";
					node->records[0]->Write();
					std::cout << "\n";
				}
			}
			else {
				if (rise) {
					for (size_t i = 0; i < node->count; i++)
					{
						WriteNode(node->children[i], deep + 1);
						for (int i = 0; i < deep; i++)
							std::cout << "   ";
						node->records[i]->Write();
						std::cout << "\n";
					}
					WriteNode(node->children[node->countSons - 1], deep + 1);
				}
				else {
					WriteKey(node->children[node->countSons - 1], deep + 1, rise);
					for (size_t i = node->countSons - 2; i > 0; i--)
					{
						for (int j = 0; j < deep; j++)
							std::cout << "   ";
						node->records[i]->Write();
						std::cout << "\n";
						WriteKey(node->children[i], deep + 1, rise);
					}
					for (int j = 0; j < deep; j++)
						std::cout << "   ";
					node->records[0]->Write();
					std::cout << "\n";
					WriteKey(node->children[0], deep + 1, rise);
				}
			}
		}
		void WriteKey(BNode* node, int deep, bool rise = true) {
			if (node == nullptr) return;
			if (node->leaf) {
				if (rise)
					for (size_t i = 0; i < node->count; i++) {
						for (int j = 0; j < deep; j++)
							std::cout << "   ";
						std::cout << criterion(*node->records[i]);
						std::cout << "\n";
					}
				else {
					for (size_t i = node->count - 1; i > 0; i--) {
						for (int j = 0; j < deep; j++)
							std::cout << "   ";
						std::cout << criterion(*node->records[i]);
						std::cout << "\n";
					}
					for (int j = 0; j < deep; j++)
						std::cout << "   ";
					std::cout << criterion(*node->records[0]);
					std::cout << "\n";
				}
			}
			else {
				if (rise) {
					for (size_t i = 0; i < node->count; i++)
					{
						WriteKey(node->children[i], deep + 1);
						for (int j = 0; j < deep; j++)
							std::cout << "   ";
						std::cout << criterion(*node->records[i]);
						std::cout << "\n";
					}
					WriteKey(node->children[node->countSons - 1], deep + 1);
				}
				else {
					WriteKey(node->children[node->countSons - 1], deep + 1, rise);
					for (size_t i = node->countSons - 2; i > 0; i--)
					{
						for (int j = 0; j < deep; j++)
							std::cout << "   ";
						std::cout << criterion(*node->records[i]);
						std::cout << "\n";
						WriteKey(node->children[i], deep + 1, rise);
					}
					for (int j = 0; j < deep; j++)
						std::cout << "   ";
					std::cout << criterion(*node->records[0]);
					std::cout << "\n";
					WriteKey(node->children[0], deep + 1, rise);
				}
			}
		}

		void InsertToNode(RECORD& value, BNode* node) {
			node->records[node->count] = &value;
			node->count = node->count + 1;
			SortNode(node);
		}

		void SortNode(BNode* node) {
			for (int i = 0; i < node->count - 1; i++) {
				for (int j = i + 1; j < node->count; j++) {
					if (criterion(*node->records[i]) > criterion(*node->records[j])) {
						auto buff = node->records[i];
						node->records[i] = node->records[j];
						node->records[j] = buff;
					}
				}
			}
		}
		void Restruct(BNode* node) {
			if (node->count < 2 * N) return;

			BNode* child1 = new BNode();
			int j;
			for (j = 0; j < N - 1; j++)
				child1->records[j] = node->records[j];
			child1->count = N - 1;
			if (node->countSons != 0) {
				for (int i = 0; i < N; i++) {
					child1->children[i] = node->children[i];
					child1->children[i]->parent = child1;
				}

				child1->leaf = false;
				child1->countSons = N - 1;
			}
			else {
				child1->leaf = true;
				child1->countSons = 0;
			}

			BNode* child2 = new BNode();
			for (int j = 0; j <= (N - 1); j++)
				child2->records[j] = node->records[j + N];
			child2->count = N;
			if (node->countSons != 0) {
				for (int i = 0; i <= N; i++) {
					child2->children[i] = node->children[i + N];
					child2->children[i]->parent = child2;
				}
				child2->leaf = false;
				child2->countSons = N;
			}
			else {
				child2->leaf = true;
				child2->countSons = 0;
			}

			if (node->parent == nullptr) {
				node->records[0] = node->records[N - 1];
				node->children[0] = child1;
				node->children[1] = child2;
				node->leaf = false;
				node->count = 1;
				node->countSons = 2;
				child1->parent = node;
				child2->parent = node;
			}
			else {
				InsertToNode(*node->records[N - 1], node->parent);
				for (int i = 0; i <= (2 * N); i++) {
					if (node->parent->children[i] == node)
						node->parent->children[i] = nullptr;
				}

				for (int i = 0; i <= (2 * N); i++) {
					if (node->parent->children[i] == nullptr) {
						for (int j = (2 * N); j > (i + 1); j--)
							node->parent->children[j] = node->parent->children[j - 1];
						node->parent->children[i + 1] = child2;
						node->parent->children[i] = child1;
						node->parent->countSons++;
						break;
					}
				}
				child1->parent = node->parent;
				child2->parent = node->parent;
				node->parent->leaf = false;
			}
		}

		void DeleteNode(BNode* node) {
			if (node != nullptr) {
				for (int i = 0; i < N; i++) {
					if (node->children[i] != nullptr) DeleteNode(node->children[i]);
					else {
						delete node;
						break;
					}
				}
			}
			root = nullptr;
		}

		bool FindKey(int value, BNode* node) {
			if (node != nullptr) {
				if (!node->leaf) {
					int i;
					for (i = 0; i < 2 * N; i++) {
						if (!(*node->records[i] == RECORD())) {
							if (value == node->GetValue(i, criterion)) return true;
							if ((value < node->GetValue(i, criterion))) {
								return FindKey(value, node->children[i]);
								break;
							}
						}
						else break;
					}
					return FindKey(value, node->children[i]);
				}
				else {
					for (int j = 0; j < node->count; j++)
						if (value == node->GetValue(j, criterion)) return true;
					return false;
				}
			}
			else return false;
		}
		bool FindKey(int value) {
			BNode* current = root;
			while (!current->leaf) {
				for (int i = 0; i < 2 * N; i++) {
					if (*current->records[i] != RECORD()) {
						if (value == criterion(*current->records[i])) {
							return true;
						}
						if (value < criterion(*current->records[i])) {
							current = current->children[i];
							break;
						}
						if (((i + 1) == current->count || *current->records[i + 1] == RECORD()) && (value > criterion(*current->records[i]))) {
							current = current->children[i + 1];
							break;
						}
					}
					else
						return false;
				}
			}
			bool result = false;
			for (int i = 0; i < current->count; i++) {
				result = result || (current->GetValue(i, criterion) == value);
			}
			return result;
		}


		RECORD GetRecordWhithKey(int value) {
			BNode* current = root;
			while (!current->leaf) {
				for (int i = 0; i < 2 * N; i++) {
					if (current->records[i] != RECORD()) {
						if (value == criterion(current->records[i])) {
							return current->records[i];
						}
						if (value < criterion(current->records[i])) {
							current = current->children[i];
							break;
						}
						if (((i + 1) == current->count || current->records[i + 1] == RECORD()) && (value > criterion(current->records[i]))) {
							current = current->children[i + 1];
							break;
						}
					}
					return RECORD();
				}
			}
			RECORD result = RECORD();
			for (int i = 0; i < current->count; i++) {
				if (current->GetValue(i) == value)
					result = current->records[i];
			}
			return result;
		}
		RECORD GetRecordWhithKey(int value, BNode* node) {
			if (node != nullptr) {
				if (!node->leaf) {
					int i;
					for (i = 0; i < 2 * N; i++) {
						if (!(*node->records[i] == RECORD())) {
							if (value == node->GetValue(i, criterion)) return *node->records[i];
							if ((value < node->GetValue(i, criterion))) {
								return GetRecordWhithKey(value, node->children[i]);
								break;
							}
						}
						else break;
					}
					return GetRecordWhithKey(value, node->children[i]);
				}
				else {
					for (int j = 0; j < node->count; j++)
						if (value == node->GetValue(j, criterion)) return *node->records[j];
					return RECORD();
				}
			}
			else return RECORD();
		}


		void Remove(int value, BNode* node) {
			BNode* current = this->root;
			int position;
			int positionSon;
			int i;
			if (!FindKey(value)) {
				return;
			}
			else {
				for (i = 0; i < current->count; i++) {
					if (*current->records[i] != RECORD()) {
						if (value == current->GetValue(i, criterion)) {
							position = i;
							break;
						}
						else {
							if ((value < current->GetValue(i, criterion))) {
								current = current->children[i];
								positionSon = i;
								i = -1;
							}
							else {
								if (i == (current->count - 1)) {
									current = current->children[i + 1];
									positionSon = i + 1;
									i = -1;
								}
							}
						}
					}
					else break;
				}
			}
			if (current->leaf) {
				if (current->count >= N)
					RemoveFromNode(value, current);
				else
					RemoveLeaf(value, current);
			}
			else
				Remove(value, current);
		}


		void RemoveFromNode(int value, BNode* node) {
			for (int i = 0; i < node->count; i++) {
				if (node->GetValue(i, criterion) == value) {
					for (int j = i; j < node->count; j++) {
						node->records[j] = node->records[j + 1];
						node->children[j] = node->children[j + 1];
					}
					node->records[node->count - 1] = nullptr;
					node->children[node->count - 1] = node->children[node->count];
					node->children[node->count] = nullptr;
					break;
				}
			}
			node->count--;
		}

		void RemoveLeaf(int value, BNode* node) {
			if ((node == root) && (node->count == 1)) {
				RemoveFromNode(value, node);
				root->children[0] = nullptr;
				delete root;
				root = nullptr;
				return;
			}
			if (node == root) {
				RemoveFromNode(value, node);
				return;
			}
			if (node->count > (N - 1)) {
				RemoveFromNode(value, node);
				return;
			}
			BNode* current = node;
			RECORD* k1;
			RECORD* k2;
			int position;
			int positionSon;
			int i;
			for (int i = 0; i <= node->count - 1; i++) {
				if (value == node->GetValue(i, criterion)) {
					position = i;
					break;
				}
			}
			BNode* parent = current->parent;
			for (int j = 0; j <= parent->count; j++) {
				if (parent->children[j] == current) {
					positionSon = j;
					break;
				}
			}

			if (positionSon == 0) {
				if (parent->children[positionSon + 1]->count > (N - 1)) {
					k1 = parent->children[positionSon + 1]->records[0];
					k2 = parent->records[positionSon];
					InsertToNode(*k2, current);
					RemoveFromNode(value, current);
					parent->records[positionSon] = k1;
					RemoveFromNode(criterion(*k1), parent->children[positionSon + 1]);
				}
				else {
					RemoveFromNode(value, current);
					if (current->count <= (N - 2))
						Repair(current);
				}
			}
			else {
				if (positionSon == parent->count) {
					if (parent->children[positionSon - 1]->count > (N - 1)) {
						BNode* temp = parent->children[positionSon - 1];
						k1 = temp->records[temp->count - 1];
						k2 = parent->records[positionSon - 1];
						InsertToNode(*k2, current);
						RemoveFromNode(value, current);
						parent->records[positionSon - 1] = k1;
						RemoveFromNode(criterion(*k1), temp);
					}
					else {
						RemoveFromNode(value, current);
						if (current->count <= (N - 2))
							Repair(current);
					}
				}
				else {
					if (parent->children[positionSon + 1]->count > (N - 1)) {
						k1 = parent->children[positionSon + 1]->records[0];
						k2 = parent->records[positionSon];
						InsertToNode(*k2, current);
						RemoveFromNode(value, current);
						parent->records[positionSon] = k1;
						RemoveFromNode(criterion(*k1), parent->children[positionSon + 1]);
					}
					else {
						if (parent->children[positionSon - 1]->count > (N - 1)) {
							BNode* temp = parent->children[positionSon - 1];
							k1 = temp->records[temp->count - 1];
							k2 = parent->records[positionSon - 1];
							InsertToNode(*k2, current);
							RemoveFromNode(value, current);
							parent->records[positionSon - 1] = k1;
							RemoveFromNode(criterion(*k1), temp);
						}
						else {
							RemoveFromNode(value, current);
							if (current->count <= (N - 2)) Repair(current);
						}
					}
				}
			}
		}

		void LConnect(BNode* node, BNode* othernode) {
			if (node == nullptr) return;
			for (int i = 0; i < othernode->count; i++) {
				node->records[node->count] = othernode->records[i];
				node->children[node->count] = othernode->children[i];
				node->count = node->count + 1;
			}
			node->children[node->count] = othernode->children[othernode->count];
			for (int j = 0; j <= node->count; j++) {
				if (node->children[j] == nullptr) break;
				node->children[j]->parent = node;
			}
			delete othernode;
		}
		void RConnect(BNode* node, BNode* othernode) {
			if (node == nullptr) return;
			for (int i = 0; i < othernode->count; i++) {
				node->records[node->count] = othernode->records[i];
				node->children[node->count + 1] = othernode->children[i + 1];
				node->count = node->count + 1;
			}
			for (int j = 0; j <= node->count; j++) {
				if (node->children[j] == nullptr) break;
				node->children[j]->parent = node;
			}
			delete othernode;
		}
		void Repair(BNode* node) {
			if ((node == root) && (node->count == 0)) {
				if (root->children[0] != nullptr) {
					root->children[0]->parent = nullptr;
					root = root->children[0];
				}
				else {
					delete root;
				}
				return;
			}
			BNode* current = node;
			RECORD k1;
			RECORD k2;
			int positionSon;

			BNode* parent = current->parent;
			for (int j = 0; j <= parent->count; j++) {
				if (parent->children[j] == current) {
					positionSon = j;
					break;
				}
			}
			if (positionSon == 0) {
				InsertToNode(*parent->records[positionSon], current);
				LConnect(current, parent->children[positionSon + 1]);
				parent->children[positionSon + 1] = current;
				parent->children[positionSon] = nullptr;
				RemoveFromNode(criterion(*parent->records[positionSon]), parent);
				if (current->count == 2 * N) {
					while (current->count == 2 * N) {
						if (current == root) {
							Restruct(current);
							break;
						}
						else {
							Restruct(current);
							current = current->parent;
						}
					}
				}
				else
					if (parent->count <= (N - 2)) Repair(parent);
			}
			else {
				if (positionSon == parent->count) {
					InsertToNode(*parent->records[positionSon - 1], parent->children[positionSon - 1]);
					LConnect(parent->children[positionSon - 1], current);
					parent->children[positionSon] = parent->children[positionSon - 1];
					parent->children[positionSon - 1] = nullptr;
					RemoveFromNode(criterion(*parent->records[positionSon - 1]), parent);
					BNode* temp = parent->children[positionSon];
					if (current->count == 2 * N) {
						while (temp->count == 2 * N) {
							if (temp == root) {
								Restruct(temp);
								break;
							}
							else {
								Restruct(temp);
								temp = temp->parent;
							}
						}
					}
					else
						if (parent->count <= (N - 2)) Repair(parent);
				}
				else {
					InsertToNode(*parent->records[positionSon], current);
					LConnect(current, parent->children[positionSon + 1]);
					parent->children[positionSon + 1] = current;
					parent->children[positionSon] = nullptr;
					RemoveFromNode(criterion(*parent->records[positionSon]), parent);
					if (current->count == 2 * N) {
						while (current->count == 2 * N) {
							if (current == root) {
								Restruct(current);
								break;
							}
							else {
								Restruct(current);
								current = current->parent;
							}
						}
					}
					else
						if (parent->count <= (N - 2))
							Repair(parent);
				}
			}
		}

	};
}


struct Table {
private:
	ARRAY array = ARRAY();
	LIST<2> list;
	TREE<2> tree;

	int* indexesCrit = 0;
	MyTypes::Criterion criterions[2];
public:

	Table(int criterionInds[2], std::string filename) {
		array = ARRAY::GetArrayFromFile(filename);
		list = LIST<2>(criterionInds);
		tree = TREE<2>(criterionInds[0]);
		for (size_t i = 0; i < 2; i++)
		{
			this->criterions[i] = MyTypes::criterions[criterionInds[i]];
		}
		for (int i = 0; i < array.Count(); i++) {
			list.PushBack(&array[i]);
			tree.Insert(array[i]);
		}
	}
	Table(int criterionInds[2], int length) {
		array = ARRAY::GetRandom(length);
		list = LIST<2>(criterionInds);
		tree = TREE<2>(criterionInds[0]);
		for (size_t i = 0; i < 2; i++)
		{
			this->criterions[i] = MyTypes::criterions[criterionInds[i]];
		}
		for (int i = 0; i < array.Count(); i++) {
			list.PushBack(&array[i]);
			tree.Insert(array[i]);
		}
	}

	struct TablePTRRecord {
		void Write() {
			record.Write();
		}
		void SetName(std::string name);
		void SetSize(unsigned int size);
		void SetWidth(unsigned short width);
		void SetHeifht(unsigned short height);
		void SetColorDepth(unsigned char colorDepth);
		void SetFormat(std::string format);

		TablePTRRecord(Table* table, RECORD& record) :record(record), table(table) {};

	private:
		RECORD& record;
		Table* table;
	};

	void SortAll();

	void WriteArray();

	void WriteSortArray(int criterion, bool rise = true);
	int FindInArray(int value, int criterion);
	TablePTRRecord operator [](int index);
	void DeleteRecordWhithArray(int value, int criterion);

	void WriteSortArrayWithTree(bool rise = true);
	RECORD FindWithTree(int value);
	void DeleteRecordFromTree(int value);


	void WriteArrayWithList();
	void WriteSortArrayWithList(int criterion, bool rise = true);
	RECORD FindRecordWithList(int value, int criterion);
	void DeleteRecordFromList(int value, int criterion);
};


void Table::TablePTRRecord::SetName(std::string name) {
	record.name = name;
	table->SortAll();
}
void  Table::TablePTRRecord::SetSize(unsigned int size) {
	record.size = size;
	table->SortAll();
}
void  Table::TablePTRRecord::SetWidth(unsigned short width) {
	record.width = width;
	table->SortAll();
}
void  Table::TablePTRRecord::SetHeifht(unsigned short height) {
	record.height = height;
	table->SortAll();
}
void  Table::TablePTRRecord::SetColorDepth(unsigned char colorDepth) {
	record.colorDepth = colorDepth;
	table->SortAll();
}
void Table::TablePTRRecord::SetFormat(std::string format) {
	record.format = format;
	table->SortAll();
}


void Table::SortAll()
{
	tree.DeleteData();
	list.DeleteData();
	for (int i = 0; i < array.Count(); i++) {
		list.PushBack(&array[i]);
		tree.Insert(array[i]);
	}
}

void Table::WriteArray()
{
	array.WriteArray();
}



void Table::WriteSortArray(int criterion, bool rise) {
	array.SortIndexes(&indexesCrit, criterions[criterion], rise);
	for (size_t i = 0; i < array.Count(); i++)
	{
		std::cout << std::to_string(indexesCrit[i]) << " ";
	}
	std::cout << "\n";
	array.WriteArray(indexesCrit);
}
int  Table::FindInArray(int value, int criterion) {
	array.SortIndexes(&indexesCrit, criterions[criterion]);
	int result = array.FindBinary<int>(indexesCrit, value, criterions[criterion]);
	if (result == -1)
		std::cout << ("������ ������ � ����� ������ ��� - " + std::to_string(value)) << "\n";
	return result;
}
Table::TablePTRRecord  Table::operator [](int index) {
	return TablePTRRecord(this, array[index]);
}

void  Table::DeleteRecordWhithArray(int value, int criterion) {
	int index = FindInArray(value, criterion);
	if (index == -1) {
		std::cout << "������� ������� ����������\n";
		return;
	}
	RECORD elem = array[index];

	array.DeleteWithNumber(elem.number);
	array.RecoverIndexes();
	SortAll();
}

void  Table::WriteSortArrayWithTree(bool rise) {
	tree.WriteTreeKeys(rise);
}
RECORD Table::FindWithTree(int value) {
	RECORD elem = tree.Find(value);
	if (elem == RECORD()) {
		std::cout << "������ ����� � ������ ���\n";
	}
	return elem;
}

void  Table::DeleteRecordFromTree(int value) {
	tree.Delete(value);
	array.RecoverIndexes();
}


void  Table::WriteArrayWithList() {
	list.WriteList();
}
void  Table::WriteSortArrayWithList(int criterion, bool rise) {
	list.WriteList(criterion, rise);
}


RECORD Table::FindRecordWithList(int value, int criterion) {
	RECORD elem = *list.Find(value, criterion);
	if (elem == RECORD()) {
		std::cout << "������ ����� � ������ ���\n";
	}
	return elem;
}


void Table::DeleteRecordFromList(int value, int criterion) {
	list.Remove(value, criterions[criterion]);
	array.RecoverIndexes();
}

int ReadValueUInt() {
	int a = 0;
	do {
		std::cin >> a;
		std::cin.ignore();
		if (a < 0)
			std::cout << "����� ������ ���� ������ ���� ����� ����\n";
	} while (a < 0);
	return a;
}
std::string ReadString() {
	std::string result = "";
	std::getline(std::cin, result);
	return result;
}

void print(std::string str = "", char end = '\n') {
	std::cout << str << end;
}

int main()
{
	srand(time(NULL));
	int criterionInds[2] = { 0,4 };
	setlocale(LC_ALL, "Rus");
	Table table = Table(criterionInds, 10);


	table.WriteArray();

	table.WriteSortArray(0, false);
	table.WriteSortArray(1, true);

	table.WriteSortArrayWithTree();



	table.WriteArrayWithList();

	table.WriteSortArrayWithList(1);
	table.WriteSortArrayWithList(2);

	table.WriteSortArrayWithList(1, false);
	table.WriteSortArrayWithList(2, false);

	print();
	int index = table.FindInArray(24, 1);
	if (index != -1)
		table[index].Write();

	print();
	table.FindRecordWithList(630, 0).Write();
	print();



	table.WriteSortArrayWithList(1, false);
	table.WriteSortArrayWithList(2, false);


	table[4].SetColorDepth(64);
	table[4].SetHeifht(4);

	table.WriteArray();
	table.WriteSortArray(1);
	table.WriteSortArrayWithTree();
	table.WriteArrayWithList();

	table.WriteSortArrayWithList(1);
	table.WriteSortArrayWithList(2);


	table.DeleteRecordWhithArray(64, 1);

	table.DeleteRecordFromTree(3223);
	table.DeleteRecordFromTree(1350);
	table.DeleteRecordFromTree(1350);

	table.WriteArray();
	table.WriteSortArray(1);

	table.WriteSortArrayWithTree(false);
	table.WriteArrayWithList();

	table.WriteSortArrayWithList(1);
	table.WriteSortArrayWithList(2);

	table.DeleteRecordFromList(8, 1);
	table.WriteSortArrayWithList(2);


}

