#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLTDataType;

typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

void SLTPrint(SLTNode* phead);
SLTNode* BuySLTNode(SLTDataType x);
void SLTPushBack(SLTNode** pphead, SLTDataType x);
void SLTPushFront(SLTNode** pphead, SLTDataType x);
void SLTPopBack(SLTNode** phead);
void SLTPopFront(SLTNode** phead);
SLTNode* FindSLTNode(SLTNode* phead, SLTDataType x);// 单链表查找

// 单链表在pos位置之后插入x
// 分析思考为什么不在pos位置之前插入？   指不回去 
void SLTInsertAfter(SLTNode* pos, SLTDataType x);
// 单链表删除pos位置之后的值
// 分析思考为什么不删除pos位置？ 指不回去
void SLTEraseAfter(SLTNode* pos);

// 单链表的销毁
void SLTDestroy(SLTNode* phead);
