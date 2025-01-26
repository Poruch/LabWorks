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
			nextListNode = nullptr;
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
	ListNode<T>* GetReverseListIt(ListNode<T>* root) {
		ListNode<T>* new_root = 0;
		while (root) {
			ListNode<T>* next = root->nextListNode;
			root->nextListNode = new_root;
			new_root = root;
			root = next;
		}
		return new_root;
	}

	template <typename T>
	ListNode<T>* GetReverseListRec(ListNode<T>* root) {
		if (root == nullptr || root->nextListNode == nullptr)
			return root;
		ListNode<T>* rest = GetReverseListRec(root->nextListNode);
		root->nextListNode->nextListNode = root;
		root->nextListNode = nullptr;
		return rest;
	}

	//Имя файла это адресс первого байта этого файла



	template <typename T>
	void AddElem(ListNode<T>** root, MyTypes::Image image, int(*criterion)(MyTypes::Image)) {
		ListNode<T>* currentNode = *root;
		ListNode<T>* res = new ListNode<T>(0, image);

		if (currentNode->GetValue(criterion) >= res->GetValue(criterion)) {
			*root = res;
			res->nextListNode = currentNode;			
		}
		else {
			if (currentNode->nextListNode == nullptr)
			{
				currentNode->nextListNode = res;
				return;
			}
			while (currentNode->nextListNode->GetValue(criterion) < res->GetValue(criterion)) {				
				currentNode = currentNode->nextListNode;
				if (currentNode->nextListNode == nullptr)
				{
					currentNode->nextListNode = res;
					return;
				}
			}
			res->nextListNode = currentNode->nextListNode;
			currentNode->nextListNode = res;			
		}
	}

	void AddElem() {
		
	}

	template <typename T>
	void GetList(ListNode<T>** root, MyTypes::Image* arr, int len, int(*criterion)(MyTypes::Image), int count = 0) {			
		*root = new ListNode<T>(0,arr[0]);
		for (size_t i = 1; i < len; i++)
		{
			AddElem(root, arr[i], criterion);
		}
		int k = 0;
		ListNode<T>* iterator = *root;
		while (iterator) {
			(iterator)->index = k++;
			iterator = (iterator)->nextListNode;
		}
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