#pragma once
#include "MyRecord.h"
#include "List.h"

namespace Trees {

template <int N, int (*criterion)(RECORD)>
struct BTree {
private:
	struct TreeNode
	{
		LIST records;
		TreeNode* children;

		int Count;

		bool leaf;

		TreeNode* GetChildren() {
			return children;
		}

		void AddValue(RECORD value) {
			records.SortedPush(value);			
		}

		bool AddChildren() {
			if (countChildren == N * 2) {
				children[countChildren++] = new TreeNode();
				return false;
			}
			children[countChildren++] = new TreeNode();
			leaf = false;
			return true;
		}

		bool IsOwerflow() {
			return records.Count() > N * 2;
		}
		TreeNode(bool isLeaf) : leaf(isLeaf) {
			records = LIST();
			children = new TreeNode[N * 2 + 1];
			countChildren = 0;
		};
		~TreeNode() {
			for (auto child : children) {
				delete child;
			}
		}
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
		delete root;
	}

	RECORD Find(int value) {
		
	}
	void Insert(RECORD record) {
		if (IsEmpty()) {
			root = new TreeNode(true);
			root->AddValue(record);
			return;
		}

		TreeNode* current = root;
		while (!current->leaf) {
			if (current->leaf) {
				current->AddValue(record);
			}
			for (int i = 0; i < current->Count; i++) {

			}
		}
	}
		
	bool IsEmpty() {
		return root == nullptr;
	}
private:	
		
	void Split();
	TreeNode* root;
	};

}