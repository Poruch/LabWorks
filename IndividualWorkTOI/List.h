#pragma once
#include "MyRecord.h"


namespace Lists {

	template <typename T>
	struct ListNode
	{
		ListNode* nextListNode;
		int index = 0;
		MyTypes::Image record;

		ListNode(int ind, MyTypes::Image im) {
			index = ind;
			record = im;
			nextListNode = new ListNode<T>();
		}

		ListNode() {
			index = 0;
			record = MyTypes::Image();
			nextListNode = nullptr;
		}

		~ListNode() {
			delete nextListNode;
		}

		T GetValue(T(*criterion)(MyTypes::Image)) {
			return criterion(record);
		}
	};

	template <typename T>
	void GetReverseList(ListNode<T>* root) {
		ListNode<T> newList(0, MyTypes::Image());
	}
	//Имя файла это адресс первого байта этого файла
	template <typename T>
	void AddElem(ListNode<T>** root, MyTypes::Image image, int(*criterion)(MyTypes::Image)) {
		
	}

	void AddElem() {

	}

	template <typename T>
	void GetList(ListNode<T>* root, MyTypes::Image* arr, int len, int(*criterion)(MyTypes::Image), int count = 0) {		
		
	}

	template <typename T>
	void WriteList(ListNode<T>* root, T(*criterion)(MyTypes::Image), bool rise = true) {
		while (root != nullptr)
		{
			std::cout << root->GetValue(criterion) << std::endl;
			root = root->nextListNode;
		}
	}

	template <typename T>
	int LFind(ListNode<T> root, MyTypes::Image value) {
		while (root != nullptr)
		{
			if (root.record == value)
				return root.index;
			root = root->nextListNode;
		}
		return - 1;
	}

	template <typename T>
	int LFind(ListNode<T> root, int value, int(*criterion)(MyTypes::Image)) {
		while (root != nullptr)
		{
			if (root.GetValue(criterion) == value)
				return root.index;
			root = root->nextListNode;
		}
		return -1;
	}

	template <typename T>
	int LFind(ListNode<T> root, std::string value, std::string(*criterion)(MyTypes::Image)) {
		while (root != nullptr)
		{
			if (root.GetValue(criterion) == value)
				return root.index;
			root = root->nextListNode;
		}
		return -1;
	}


};