#include "List.h"

namespace Lists {


	void List::SortedPush(RECORD value, int (*criterion)(RECORD), bool rise) {
		count++;
		int val = criterion(value);
		Node* newPointer = new Node(count, value);

		if (IsEmpty()) {
			first = newPointer;
			last = newPointer;
			return;
		}
		if (val <= first->GetValue(criterion) == rise) {
			Push(value);
			return;
		}
		if (val >= last->GetValue(criterion) == rise) {
			PushBack(value);
			return;
		}
		Node* slow = first;
		Node* fast = first->nextNode;
		while (fast &&  (val > fast->GetValue(criterion) == rise) ) {
			slow = fast;
			fast = fast->nextNode;
		}
		slow->nextNode = newPointer;
		newPointer->nextNode = fast;
	}

	void List::PushBack(RECORD value) {
		count++;
		Node* newPointer = new Node(count, value);
		if (IsEmpty()) {
			first = newPointer;
			last = newPointer;
			return;
		}
		last->nextNode = newPointer;
		last = newPointer;
	}

	void List::Push(RECORD value) {
		count++;
		Node* newPointer = new Node(count, value);
		if (IsEmpty()) {
			first = newPointer;
			last = newPointer;
			return;
		}
		newPointer->nextNode = first;
		first = newPointer;
	}

	void List::RemoveFirst() {
		if (IsEmpty()) return;
		Node* current = first;
		first = current->nextNode;
		delete current;
	}

	void List::RemoveLast() {
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

	Node* List::operator[] (const int index) {
		if (IsEmpty()) return nullptr;
		Node* current = first;
		for (int i = 0; i < index; i++) {
			current = current->nextNode;
			if (!current) return nullptr;
		}
		return current;
	}

	void List::WriteList() {
		if (IsEmpty()) return;
		Node* current = first;

		std::cout << "////////////////////////////////////////////////////////////////\n";
		std::cout << "Number///Name///Size///Width///Height///ColorDepth///Format///\n";
		while (current)
		{
			current->record.Write();
			std::cout << std::endl;
			current = current->nextNode;
		}
		std::cout << "////////////////////////////////////////////////////////////////\n";
	}

	void List::ReverseIter() {
		last = first;
		Node* buffer = GetReverseListIt(first);
		first = buffer;
	}

	void List::ReverseRec() {
		last = first;
		Node* buffer = GetReverseListRec(first);
		first = buffer;
	}

	Node* List::GetReverseListIt(Node* root) {
		Node* new_root = 0;
		while (root) {
			Node* next = root->nextNode;
			root->nextNode = new_root;
			new_root = root;
			root = next;
		}
		return new_root;
	}

	Node* List::GetReverseListRec(Node* root) {
		if (root == nullptr || root->nextNode == nullptr)
			return root;
		Node* rest = GetReverseListRec(root->nextNode);
		root->nextNode->nextNode = root;
		root->nextNode = nullptr;
		return rest;
	}
	RECORD List::PopFirst()
	{
		RECORD result = first->record;
		Node* deleting = first;
		first = first->nextNode;
		delete deleting;
		return result;
	}
	RECORD List::PopLast()
	{
		RECORD result = last->record;
		Node* prelast = operator[](count - 1);		
		Node* deleting = last;
		last = prelast;
		delete deleting;
		return result;
	}
}