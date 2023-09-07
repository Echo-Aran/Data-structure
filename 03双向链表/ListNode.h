#pragma once
#include<stdio.h>
#include<stdlib.h>//malloc free 的函数
#include<stdbool.h>//bool
#include<assert.h>//assert
typedef int LTDataType;//typedef 后面要加;
typedef struct ListNode
{
	LTDataType data;
	struct ListNode* prev;
	struct ListNode* next;

}ListNode;
//创建一个新的节点
ListNode* BuyNewnode(LTDataType x);
//创建一个链表的头节点
ListNode* Init();
//判断一个链表是否为自身循环
bool Empty(ListNode* phead);
//双向链表的销毁
ListNode* Destroy(ListNode* phead);
//双向链表打印
void Print(ListNode* phead);
//双向链表尾插
void PushBack(ListNode* phead,LTDataType x);
//尾删
void PopBack(ListNode* phead);
//头插
void PushFront(ListNode* phead, LTDataType x);
//头删
void PopFront(ListNode* phead);
//查找
ListNode* Find(ListNode*phead,LTDataType x);
//在pos位置前插入
void ListInsert(ListNode* pos, LTDataType x);
//删除pos位置的节点
