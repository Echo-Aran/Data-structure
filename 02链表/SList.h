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
SLTNode* FindSLTNode(SLTNode* phead, SLTDataType x);// ���������

// ��������posλ��֮�����x
// ����˼��Ϊʲô����posλ��֮ǰ���룿   ָ����ȥ 
void SLTInsertAfter(SLTNode* pos, SLTDataType x);
// ������ɾ��posλ��֮���ֵ
// ����˼��Ϊʲô��ɾ��posλ�ã� ָ����ȥ
void SLTEraseAfter(SLTNode* pos);

// �����������
void SLTDestroy(SLTNode* phead);
