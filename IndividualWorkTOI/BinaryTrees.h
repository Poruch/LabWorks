#pragma once
#include "MyRecord.h"

namespace Trees {}

//	struct TreeNode
//	{
//		int index = 0;
//		MyTypes::Image record;
//
//
//		TreeNode(int ind, MyTypes::Image im) {
//			index = ind;
//			record = im;
//		}
//
//		template <typename T>
//		T GetValue(T(*criterion)(MyTypes::Image)) {
//			return criterion(record);
//		}
//		TreeNode* leftChild = nullptr;
//		TreeNode* rightChild = nullptr;
//
//	};
//	struct Tree {
//		TreeNode* root;
//
//	};
//	template <typename T>
//	void AddElem(TreeNode<T>* root, MyTypes::Image image, int(*criterion)(MyTypes::Image), int index) {
//		if (criterion(image) > criterion(root->record)) {
//			if (root->rightChild == nullptr)
//				root->rightChild = new TreeNode<T>(index,image);
//			else
//				AddElem(root->rightChild, image, criterion,index);
//		}
//		else if (criterion(image) < criterion(root->record)) {
//			if (root->leftChild == nullptr)
//				root->leftChild = new TreeNode<T>(index, image);
//			else
//				AddElem(root->leftChild, image, criterion, index);
//		}
//	}
//
//	template <typename T>
//	void GetTree(TreeNode<T>* root, MyTypes::Image* arr, int len, int(*criterion)(MyTypes::Image), int count = 0) {
//		(*root) = TreeNode<T>(0, arr[0]); 
//		for (int i = 1; i < len; i++) {
//			AddElem(root, arr[i], criterion,i);
//		}
//	}
//
//
//
//	template <typename T>
//	void WriteTree(TreeNode<T>* root, T(*criterion)(MyTypes::Image),bool rise = true) {
//		if (rise) {
//			if (root != nullptr) {
//				WriteTree(root->leftChild, criterion,rise);
//				std::cout << root->GetValue(criterion) << std::endl;
//				WriteTree(root->rightChild, criterion,rise);
//			}
//		}
//		else {
//			if (root != nullptr) {
//				WriteTree(root->rightChild, criterion, rise);
//				std::cout << root->GetValue(criterion) << std::endl;
//				WriteTree(root->leftChild, criterion,rise);
//			}
//		}
//	}
//	template <typename T>
//	int TFind(TreeNode root, T value, T(*criterion)(MyTypes::Image)) {
//		if (root != nullptr) {
//			if (value == criterion(root.record))
//				return root.index;
//			else if(value <= criterion(root.record))
//				return TFind(root->leftChild, value);
//			else 
//				return TFind(root->rightChild, value);
//		}
//		return -1;
//	}
//}