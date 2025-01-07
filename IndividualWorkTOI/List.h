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

		T GetValue(T(*criterion)(MyTypes::Image)) {
			return criterion(record);
		}
	};

	template <typename T>
	void GetReverseList(ListNode<T>* root) {
		ListNode<T> newList(0, MyTypes::Image());

	}

	template <typename T>
	void AddElem(ListNode<T>* root, MyTypes::Image image, int(*criterion)(MyTypes::Image)) {
		ListNode<T>* currentNode = root;		
		while (currentNode->nextListNode != nullptr) {
			currentNode = currentNode->nextListNode;
		}
		currentNode->nextListNode = ListNode<T>(currentNode->index+1,image);
	}

	template <typename T>
	void GetList(ListNode<T>* root, MyTypes::Image* arr, int len, int(*criterion)(MyTypes::Image), int count = 0) {
		
		*root = ListNode<T>(0,arr[0]);
		ListNode<T>* currentNode = root;
		for (int i = 1; i < len; i++)
		{
			currentNode->nextListNode = new ListNode<T>(i,arr[i]);
			currentNode = currentNode->nextListNode;
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

		return - 1;
	}

	template <typename T>
	int LFind(ListNode<T> root, int value, int(*criterion)(MyTypes::Image)) {
		return -1;
	}

	template <typename T>
	int LFind(ListNode<T> root, std::string value, std::string(*criterion)(MyTypes::Image)) {
		return -1;
	}


};