#include<iostream>
using namespace std;
#include"BinarySearchTree.h"
void TestBSTree1()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	BSTree<int> t;
	for (auto e : a)
	{
		t.Insert(e);
	}

	t.InOrder();

	t.Erase(4);
	t.InOrder();

	t.Erase(6);
	t.InOrder();

	t.Erase(7);
	t.InOrder();

	t.Erase(3);
	t.InOrder();

	for (auto e : a)
	{
		t.Erase(e);
	}
	t.InOrder();
}
void TestBSTree2()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	BSTree<int> t;
	for (auto e : a)
	{
		t.InsertR(e);
	}

	BSTree<int> t1(t);

	t.InOrder();
	t1.InOrder();


	t.EraseR(4);
	t.InOrder();

	t.EraseR(6);
	t.InOrder();

	t.EraseR(7);
	t.InOrder();

	t.EraseR(3);
	t.InOrder();

}

int main() {
	TestBSTree1();
	TestBSTree2();

	return 0;
}