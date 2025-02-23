#pragma once
#include "MyRecord.h"
#include "Array.h"

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
			records = new RECORD*[2 * N];
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
		return GetRecordWhithKey(value,root);
	}

	bool Contains(int value) {
		return FindKey(value,root);
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
			while(!current->leaf) {
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
		WriteNode(root,0,rise);
	}
	void WriteTreeKeys(bool rise = true) {
		WriteKey(root, 0,rise);
	}
	
	bool IsEmpty() {
		return root == nullptr;
	}
private:	
	void WriteNode(BNode* node, int deep, bool rise = true) {
		if (node == nullptr) return;
		if (node->leaf) {
			for (size_t i = 0; i < node->count; i++)
			{
				for (int i = 0; i < deep; i++)
					std::cout << "   ";
				node->records[i]->Write();
				std::cout << "\n";
			}
		}
		else {
			for (size_t i = 0; i < node->count; i++)
			{
				WriteNode(node->children[i], deep + 1);
				for (int i = 0; i < deep; i++)
					std::cout << "   ";
				node->records[i]->Write();
				std::cout << "\n";
			}
			WriteNode(node->children[node->countSons - 1],deep + 1);
		}
	}
	void WriteKey(BNode* node, int deep, bool rise = true) {
		if (node == nullptr) return;
		if (node->leaf) {
			for (size_t i = 0; i < node->count; i++)
			{
				for (int i = 0; i < deep; i++)
					std::cout <<  "   ";
				std::cout << criterion(*node->records[i]);
				std::cout << "\n";
			}
		}
		else {
			for (size_t i = 0; i < node->count; i++)
			{
				WriteKey(node->children[i], deep + 1);
				for (int i = 0; i < deep; i++)
					std::cout << "   ";
				std::cout << criterion(*node->records[i]);
				std::cout << "\n";
			}
			WriteKey(node->children[node->countSons - 1], deep + 1);
		}
	}

	void InsertToNode(RECORD& value, BNode* node) {
		node->records[node->count] = &value;
		node->count = node->count + 1;
		SortNode(node);
	}

	void SortNode(BNode* node) {
		for (int i = 0; i < node->count -1; i++) {
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
				for (i = 0; i < 2 * N ; i++) {
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
			result =  result || (current->GetValue(i,criterion) ==value);
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
			for (i = 0; i < current->count ; i++) {
				if (*current->records[i] != RECORD()) {
					if (value == current->GetValue(i,criterion)) {
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
			if (current->count >= N )
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
	BNode* root;
	};
}

