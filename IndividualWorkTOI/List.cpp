#include "List.h"
//#include "List.h"
#define CRITERION(i) criterions[i]
namespace Lists {

	template<int N>
	RECORD List<N>::Find(int value, int criterionInd) {
		Node* current = first[criterionInd];
		while (current && current->GetValue(criterions[criterionInd]) != value) {
			current = current->nextNode;
		}
		return current->record;
	}


	template<int N>
	void List<N>::SortedPush(RECORD value) {
		count++;
		for (int i = 1; i < N + 1; i++) {
			int val = CRITERION()(value);
			Node* newPointer = new Node(count, value);

			if (IsEmpty(i)) {
				first[i] = newPointer;
				last[i] = newPointer;
				return;
			}
			if (val <= first[i]->GetValue(CRITERION)) {
				Push(value);
				return;
			}
			if (val >= last[i]->GetValue(CRITERION)) {
				PushBack(value);
				return;
			}
			Node* slow = first[i];
			Node* fast = first[i]->nextNode;
			while (fast && (val > fast->GetValue(CRITERION))) {
				slow = fast[i];
				fast = fast[i]->nextNode;
			}
			slow->nextNode = newPointer;
			newPointer->nextNode = fast;
		}
	}

	template<int N>
	void List<N>::PushBack(RECORD value) {
		Node* newPointer = new Node(count, value);
		if (IsEmpty()) {
			first[0] = newPointer;
			last[0] = newPointer;
			return;
		}
		last[0]->nextNode = newPointer;
		last[0] = newPointer;
	}

	//template<int N>
	//void List<N>::Push(RECORD value) {
	//	count++;
	//	Node* newPointer = new Node(count, value);
	//	if (IsEmpty()) {
	//		first = newPointer;
	//		last = newPointer;
	//		return;
	//	}
	//	newPointer->nextNode = first;
	//	first = newPointer;
	//}

	template<int N>
	void List<N>::RemoveFirst() {
		if (IsEmpty()) return;
		Node* current = first;
		first = current->nextNode;
		delete current;
	}

	template<int N>
	void List<N>::RemoveLast() {
		if (IsEmpty()) return;
		if (first == last) {
			RemoveFirst();
			return;
		}
		Node* current = first;
		while (current->nextNode != last) current = current->nextNode;
		current->nextNode = nullptr;
		delete last;
		last = current;
	}

	template<int N>
	List<N>::Node* List<N>::operator[] (const int index) {
		if (IsEmpty()) return nullptr;
		Node* current = first;
		for (int i = 0; i < index; i++) {
			current = current->nextNode;
			if (!current) return nullptr;
		}
		return current;
	}

	template<int N>
	void List<N>::WriteList() {
		if (IsEmpty()) return;
		Node* current = first[0];

		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number/1 Name/2 Size/3 Width/4 Height/5 ColorDepth/6 Format///\n";
		while (current)
		{
			current->record.Write();
			std::cout << std::endl;			
			current = current->nextNode;
			if (current) {
				std::cout << "\t\t|" << std::endl;
				std::cout << "\t\tV" << std::endl;
			}
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	template<int N>
	void List<N>::ReverseIter() {
		last = first;
		Node* buffer = GetReverseListIt(first);
		first = buffer;
	}
	template<int N>
	void List<N>::ReverseRec() {
		last = first;
		Node* buffer = GetReverseListRec(first);
		first = buffer;
	}

	template<int N>
	List<N>::Node* List<N>::GetReverseListIt(Node* root) {
		Node* new_root = 0;
		while (root) {
			Node* next = root->nextNode;
			root->nextNode = new_root;
			new_root = root;
			root = next;
		}
		return new_root;
	}

	template<int N>
	List<N>::Node* List<N>::GetReverseListRec(Node* root) {
		if (root == nullptr || root->nextNode == nullptr)
			return root;
		Node* rest = GetReverseListRec(root->nextNode);
		root->nextNode->nextNode = root;
		root->nextNode = nullptr;
		return rest;
	}

	template<int N>
	RECORD List<N>::PopFirst()
	{
		RECORD result = first->record;
		Node* deleting = first;
		first = first->nextNode;
		delete deleting;
		return result;
	}

	template<int N>
	RECORD List<N>::PopLast()
	{
		RECORD result = last->record;
		Node* prelast = operator[](count - 1);		
		Node* deleting = last;
		last = prelast;
		delete deleting;
		return result;
	}

	template<int N>
	void List<N>::Remove(int value, int criterionInd) {
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

	template<int N>
	void List<N>::WriteList() {
		if (IsEmpty()) return;
		Node* current = first;
		while (current)
		{
			std::cout << current->GetValue(criterion) << std::endl;
			current = current->nextNode;
		}
	}

	template<int N>
	void List<N>::WriteList(int criterionInd) {
		if (IsEmpty()) return;
		Node* current = first;
		while (current)
		{
			std::cout << current->GetValue(criterion) << std::endl;
			current = current->nextNode;
		}
	}

	

}