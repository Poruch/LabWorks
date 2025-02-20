#pragma once
#include "MyRecord.h"

#define RECORD MyTypes::Image
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
		typedef int (*Criterion)(RECORD&);

		RECORD Find(int value, int criterionInd) {
			Node* current = first[criterionInd];
			while (current && current->GetValue(CRITERION(criterionInd)) != value) {
				current = current->nextNode;
			}
			return current->record;
		}
		List(Criterion criterions[N]) {
			static_assert(N > 0 && N <= 6, " оличество критериев должно быть больше 0");
			for (size_t i = 0; i < N; i++) {
				this->criterions[i] = criterions[i];
				first[i] = nullptr;
				last[i] = nullptr;
			}
			first[N] = nullptr;
			last[N] = nullptr;
			count = 0;
		}
		int count;
		int Count() {
			return count;
		}

		bool IsEmpty() {
			bool result = true;
			for (int i = 0; i < N+1; i++) {
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
					SortedPush(value, i+1);
				}
				return;
			}
			newPointer->nextNode = first[0];
			first[0] = newPointer;
			for (int i = 0; i < N; i++) {
				SortedPush(value, i+1);
			}

		}

		
		void PushBack(RECORD* value) {
			count++;
			Node* newPointer = new Node(count, value);
			if (IsEmpty(0)) {
				first[0] = newPointer;
				last[0] = newPointer;
				return;
			}
			last[0]->nextNode = newPointer;
			last[0] = newPointer;
			for (int i = 0; i < N; i++) {
				SortedPush(value, i);
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
			last = first[IndCriterion];
			Node* buffer = GetReverseListIt(first[IndCriterion]);
			first = buffer;
		}
		void ReverseRec(int IndCriterion) {
			last = first[IndCriterion];
			Node* buffer = GetReverseListRec(first[IndCriterion]);
			first = buffer;
		}

		void Remove(int value, Criterion criterion) {
			if (IsEmpty(0)) return;
			
			if (first[0] == last[0]) {
				for (size_t i = 0; i < N + 1; i++)	{
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
		void WriteList(int criterionInd) {
			if (IsEmpty(criterionInd)) return;
			Node* current = first[criterionInd];
			int offSet = 0;
			if (criterionInd == 0) {
				WriteList();
				return;
			}
			
			while (MyTypes::criterions[offSet] != criterions[criterionInd - 1]) offSet++;
			offSet++;
			std::cout << "////////////////////////////////////////////////////////////////\n";
			std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
			while (current)
			{
				if(current->record != NULL)
					current->record->Write();
				std::cout << std::endl;
				current = current->nextNode;
				if (current) {
					for (int i = 0; i < offSet; i++)
						std::cout << "\t";
					std::cout << "|" << std::endl;
					for (int i = 0; i < offSet; i++)
						std::cout << "\t";
					std::cout << "V" << std::endl;
				}
			}
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


		Criterion criterions[N];
		Node* first[N + 1];
		Node* last[N + 1];
	};
};