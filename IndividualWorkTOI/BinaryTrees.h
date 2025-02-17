#pragma once
#include "MyRecord.h"
#include "Array.h"
#define ARRAY Arrays::MyArray

namespace Trees {

template <int N,int (*criterion)(RECORD)>
struct BTree {
private:
	struct BNode
	{
		ARRAY records;

		BNode* children[2 * N + 1];
		BNode* parent;

		int count;
		int countSons;
		bool leaf;

		BNode() : leaf(true) {
			records = Arrays::MyArray(2 * N);

			for (int i = 0; i <= records.Count(); i++) children[i] = nullptr;
			parent = nullptr;
			count = 0;
			countSons = 0;
		};
		BNode(bool isLeaf) : leaf(isLeaf) {
			records = ARRAY(2 * N);

			for (int i = 0; i <= 2 * N; i++) children[i] = nullptr;
			parent = nullptr;
			count = 0;
			countSons = 0;
		};

		template <typename T>
		T GetValue(int index, T(*criterion)(RECORD)) {
			return criterion(records[index]);
		}	
		
		RECORD& operator[](int index) {
			return records[index];
		}
	};
public:
	BTree() {
		root = nullptr;

	} 
	~BTree() {
		if (root != nullptr)
			DeleteNode(root);
	}

	RECORD Find(int value) {
		return RECORD();
	}

	bool Contains(int value) {
		return false;
	}

	void Insert(RECORD value) {
		if (IsEmpty()) {
			BNode* newRoot = new BNode();
			newRoot->records[0] = value;
			newRoot->count++;
			root = newRoot;
		}
		else {
			BNode* current = root;
			while(!current->leaf) {
				for (int i = 0; i < 2 * N; i++) {
					if (current->records[i] != RECORD()) {
						if (criterion(value) <= criterion(current->records[i])) {
							current = current->children[i];
							break;
						}
						if (((i + 1) == current->count || current->records[i + 1] == RECORD()) && (criterion(value) > criterion(current->records[i]))) {
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

	void Delete() {

	}
	
	void WriteTree() {
		WriteNode(root);
	}

	
	bool IsEmpty() {
		return root == nullptr;
	}
private:	
	void WriteNode(BNode* node) {
		if (node == nullptr) return;
		if (node->leaf) {
			for (size_t i = 0; i < node->count; i++)
			{
				node->records[i].Write();
				std::cout << "\n";
			}
		}
		else {
			for (size_t i = 0; i < node->count; i++)
			{
				WriteNode(node->children[i]);
				node->records[i].Write();
				std::cout << "\n";
			}
			WriteNode(node->children[node->countSons - 1]);
		}
	}
	void InsertToNode(RECORD value, BNode* node) {
		node->records[node->count] = value;
		node->count = node->count + 1;
		node->records.Sort(0,node->count,criterion);
	}
	void Restruct(BNode* node) {
		if (node->count < 2 * N ) return;

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
			for (int i = 0; i <= N ; i++) {
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
			InsertToNode(node->records[N - 1], node->parent);
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
			for (int i = 0; i < 2 * N; i++) {
				if (node->children[i] != nullptr) DeleteNode(node->children[i]);
				else {
					delete node;
					break;
				}
			}
		}
	}


	bool FindKey(int key, BNode* node) {
		return true;
	}
	RECORD GerRecordWhithKey(int key, BNode* node) {
		return RECORD();
	}

	void remove(int key, BNode* node);
	void removeFromNode(int key, BNode* node);
	void removeLeaf(int key, BNode* node);
	void lconnect(BNode* node, BNode* othernode);
	void rconnect(BNode* node, BNode* othernode);
	void repair(BNode* node);
	void Split();


	BNode* root;

	};

}

