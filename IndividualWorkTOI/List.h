#pragma once
#include "MyRecord.h"
#define RECORD MyTypes::Image
#define LIST Lists::List

namespace Lists {

	
	struct Node
	{
		Node* nextNode;
		int index = 0;
		RECORD record;

		Node(int ind, RECORD im) {
			index = ind;
			record = im;
			nextNode = nullptr;
		}
		Node() {
			index = 0;
			record = RECORD();
			nextNode = nullptr;
		}


		template <typename T>
		T GetValue(T(*criterion)(RECORD)) {
			return criterion(record);
		}
		

	};
	struct List {
		Node* first;
		Node* last;
		List() {
			first = nullptr;
			last = nullptr;
			count = 0;
		}
		int count;
		int Count() {
			return count;
		}

		bool IsEmpty() {
			return first == nullptr;
		}


		void SortedPush(RECORD value, int (*criterion)(RECORD), bool rise = true);
		void PushBack(RECORD value);
		void Push(RECORD value);
		void RemoveFirst();
		void RemoveLast();
		Node* operator[] (const int index);
		void WriteList();
		void ReverseIter();
		void ReverseRec();
		Node* GetReverseListIt(Node* root);
		Node* GetReverseListRec(Node* root);


		template <typename T>
		void Remove(T value, T(*criterion)(RECORD)) {
			if (IsEmpty()) return;
			if (first->GetValue(criterion) == value) {
				RemoveFirst();
				return;
			}
			else if (last->GetValue(criterion) == value) {
				RemoveLast();
				return;
			}
			Node* slow = first;
			Node* fast = first->nextNode;
			while (fast && fast->GetValue(criterion) != value) {
				fast = fast->nextNode;
				slow = slow->nextNode;
			}
			if (!fast) {
				std::cout << "This element does not exist" << std::endl;
				return;
			}
			slow->nextNode = fast->nextNode;
			delete fast;
		}

		template <typename T>
		void WriteList(T(*criterion)(RECORD)) {
			if (IsEmpty()) return;
			Node* current = first;
			while (current)
			{
				std::cout << current->GetValue(criterion) << std::endl;
				current = current->nextNode;
			}
		}		

		template <typename T>
		Node* LFind(T value, T(*criterion)(RECORD)) {
			Node* current = first;
			while (current && current->GetValue(criterion) != value) {
				current = current->nextNode;
			}
			return current;
		}
	};
};