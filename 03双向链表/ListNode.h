#pragma once
#include<stdio.h>
#include<stdlib.h>//malloc free �ĺ���
#include<stdbool.h>//bool
#include<assert.h>//assert
typedef int LTDataType;//typedef ����Ҫ��;
typedef struct ListNode
{
	LTDataType data;
	struct ListNode* prev;
	struct ListNode* next;

}ListNode;
//����һ���µĽڵ�
ListNode* BuyNewnode(LTDataType x);
//����һ�������ͷ�ڵ�
ListNode* Init();
//�ж�һ�������Ƿ�Ϊ����ѭ��
bool Empty(ListNode* phead);
//˫�����������
ListNode* Destroy(ListNode* phead);
//˫�������ӡ
void Print(ListNode* phead);
//˫������β��
void PushBack(ListNode* phead,LTDataType x);
//βɾ
void PopBack(ListNode* phead);
//ͷ��
void PushFront(ListNode* phead, LTDataType x);
//ͷɾ
void PopFront(ListNode* phead);
//����
ListNode* Find(ListNode*phead,LTDataType x);
//��posλ��ǰ����
void ListInsert(ListNode* pos, LTDataType x);
//ɾ��posλ�õĽڵ�
