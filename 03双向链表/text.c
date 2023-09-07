#include"ListNode.h"
void Test01()
{
	ListNode* plist = Init();
	PushBack(plist, 1);
	PushBack(plist, 2);
	PushBack(plist, 3);
	PushBack(plist, 4);
	PushBack(plist, 5);
	Print(plist);
}
void Test02()
{
	ListNode* plist = Init();
	PushBack(plist, 1);
	PushBack(plist, 2);
	PushBack(plist, 3);
	PushBack(plist, 4);
	PushBack(plist, 5);
	Print(plist);

	PopBack(plist);
	PopBack(plist);
	Print(plist);

}
void Test03()
{
	ListNode* plist = Init();
	PushBack(plist, 1);
	PushBack(plist, 2);
	PushBack(plist, 3);
	PushBack(plist, 4);
	PushBack(plist, 5);
	Print(plist);

	PushFront(plist, 1);
	PushFront(plist, 2);
	PushFront(plist, 3);
	Print(plist);



}
void Test04()
{
	ListNode* plist = Init();
	PushBack(plist, 1);
	PushBack(plist, 2);
	PushBack(plist, 3);
	PushBack(plist, 4);
	PushBack(plist, 5);
	Print(plist);

	PopFront(plist);
	PopFront(plist);
	PopFront(plist);
	Print(plist);
}
int main()
{
	Test01();
	Test02();
	Test03();
	Test04();
}