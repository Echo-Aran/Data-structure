#include"SList.h"
void SLTPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL");
	printf("\n");
}//能不能用phead 直接遍历

SLTNode* BuySLTNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		return NULL;
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySLTNode(x);
	SLTNode* tail = *pphead;//指针指向一个地址 &...
	newnode->next = NULL;
	if (*pphead = NULL)
	{
		*pphead = newnode;//  解引用的过程
	}
	else
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

void SLTPushFront(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySLTNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}

//void SLTpopBack(SLTNode* phead)
//{
//	assert(phead);
//	/*if (phead->next == NULL)
//	{
//		free(phead);
//
//	}*/
//	SLTNode* tail = phead;
//	while (tail->next->next != NULL)
//	{
//		tail = tail->next;
//	}
//	free(tail->next);
//	tail->next = NULL;
//}

void SLTPopBack(SLTNode** pphead)
{
	assert(*pphead);
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLTNode* tail = *pphead;
		while (tail->next->next != NULL)
		{
			tail = tail->next;
		}
		free(tail->next);
		tail->next = NULL;
	}
	
}

void SLTPopFront(SLTNode** phead)
{
	assert(*phead);
	SLTNode* first = *phead;
	*phead = first->next;
	free(first);
	first = NULL;
}

SLTNode* FindSLTNode(SLTNode* phead, SLTDataType x)
{
	if (phead->next->data == x)
	{
		return phead->next;
	}
	else
	{
		phead = phead->next;
	}
}
void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
	SLTNode*newnode= BuySLTNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

void SLTEraseAfter(SLTNode* pos)
{
	assert(pos->next);
	SLTNode* tmp = pos->next;
	pos->next = pos->next->next;
	free(tmp);
	tmp = NULL;
}

void SLTDestroy(SLTNode** phead)
{
	while ((*phead)->next!= NULL)
	{
		SLTEraseAfter(*phead);
	}
	free(*phead);
	*phead = NULL;
}