// IndividualWorkTOI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "InputManager.h"
#include "MyRecord.h"
#include "Array.h"
#include "BinaryTrees.h"
#include "List.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	MyTypes::Image* im = 0;
	int len = 0;
	Arrays::GetArrayFromFile(&im, &len,"Data.txt");
	Arrays::WriteArray(im,len);
	Trees::TreeNode<int> root(0,MyTypes::Image());
	Trees::GetTree<int>(&root, im, len, [](MyTypes::Image im) {return (int)im.height; });
	Trees::WriteTree<int>(&root, [](MyTypes::Image im) { return (int)im.height; }, false);

	Lists::ListNode<int> list(0, MyTypes::Image());
	Lists::GetList<int>(&list,im,len, [](MyTypes::Image im) { return (int)im.height; });
	Lists::WriteList<int>(&list, [](MyTypes::Image im) { return (int)im.height; });


}

